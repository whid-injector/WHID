/*
 * WHID Injector - ESP Sketch
 * http://whid.ninja
 * Forked by Luca Bongiorni
 * Based on ESPloit by Corey Harding of www.LegacySecurityGroup.com
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>


// #############################################
// ######## WiFi Configuration Defaults ########
// #############################################
int wifi_accesspointmode = 1; // set to 0 to connect to an existing network or leave it set to 1 to use the esp8266 as an access point
char wifi_ssid[32] = "WHID-Injector";
char wifi_password[64] = "Vivalaf1g@";
int wifi_channel = 6;
int wifi_hidden = 0; // Set as 0 to broadcast AP's SSID or as 1 to hide SSID
// #############################################
// ######## WiFi Configuration Defaults ########
// #############################################


int DelayLength = 2000; //Length of time in ms to wait between sending lines from payload
IPAddress local_IP(192,168,1,1); //IP of the esp8266 server
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
ESP8266WebServer server(80);
File fsUploadFile;
File fsConfigFile;
String webString;

const String HTML_CSS_STYLING = "<style>a,body{background-color: #000;color: #0f0;}</style>";
const String HTML_BACK_TO_INDEX = "<a href=\"/\"><- BACK TO INDEX</a><br><br>";
const String CONFIG_FILE = "/whid_config.ini";

void loadConfig(){
  fsConfigFile = SPIFFS.open(CONFIG_FILE, "r");
  if (!fsConfigFile)
  {
    writeConfig();
  }
  while (fsConfigFile.available())
  {
    String line = fsConfigFile.readStringUntil('\n');
    line.trim();
    if (line.startsWith("#")) continue;
    int equalsSignPosition = line.indexOf("=");
    if (equalsSignPosition == -1) continue;
    
    String key = line.substring(0,equalsSignPosition);
    String val = line.substring(equalsSignPosition + 1);
    key.trim();
    val.trim();
    setValue(key, val);
  }
  fsConfigFile.close();
}

void setValue(String name, String value){
  if (name == "DelayLength")
    DelayLength = value.toInt();
  else if (name == "AccessPointMode")
    wifi_accesspointmode = constrain(value.toInt(), 0, 1);
  else if (name == "WiFiSSID")
     value.toCharArray(wifi_ssid, sizeof(wifi_ssid));
  else if (name == "WiFiPass")
     value.toCharArray(wifi_password, sizeof(wifi_password));
  else if (name == "WiFiChannel")
    wifi_channel = constrain(value.toInt(), 0, 13);
  else if (name == "WiFiHidden")
    wifi_hidden = constrain(value.toInt(), 0, 1);
}

void writeConfig(){
  SPIFFS.remove(CONFIG_FILE);
  fsConfigFile = SPIFFS.open(CONFIG_FILE, "a");
  String line;
  if(fsConfigFile)
  {
    line = String("DelayLength=") + String(DelayLength);
    fsConfigFile.println(line);
    line = String("AccessPointMode=") + String(wifi_accesspointmode);
    fsConfigFile.println(line);
    line = String("WiFiSSID=") + String(wifi_ssid);
    fsConfigFile.println(line);
    line = String("WiFiPass=") + String(wifi_password);
    fsConfigFile.println(line);
    line = String("WiFiChannel=") + String(wifi_channel);
    fsConfigFile.println(line);
    line = String("WiFiHidden=") + String(wifi_hidden);
    fsConfigFile.println(line);
    fsConfigFile.close();
  }
}

void handleFileUpload(){
  if(server.uri() != "/upload") return;
  HTTPUpload& upload = server.upload();
  if(upload.status == UPLOAD_FILE_START){
    String filename = upload.filename;
    filename = "/payloads/"+filename;
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  }
  else if(upload.status == UPLOAD_FILE_WRITE){
    if(fsUploadFile)
    fsUploadFile.write(upload.buf, upload.currentSize);
  }
  else if(upload.status == UPLOAD_FILE_END){
    if(fsUploadFile)
    fsUploadFile.close();
  }
}

void ListPayloads(){
  String FileList = HTML_CSS_STYLING + HTML_BACK_TO_INDEX + "<h><b>Choose Payload:</b></h><br><br>";
  Dir dir = SPIFFS.openDir("/payloads");
  while (dir.next()){
    String FileName = dir.fileName();
    File f = dir.openFile("r");
    FileList += " ";
    FileList += "<a href=\"/showpayload?payload="+FileName+"\">"+FileName+"</a>"+"<br>";
  }
  server.send(200, "text/html", FileList);
}

String GetConfigForm(){
  return (String)"<form method='POST' action='/config/update'><p>"
  + "Delay length (ms): <input type='number' name='DelayLength' value='" + DelayLength + "'>"
  + "<br>Channel: <input type='number' name='WiFiChannel' value='" + wifi_channel + "'>"
  + "<br>SSID: <input type='text' name='WiFiSSID' value='" + wifi_ssid + "'>"
  + "<br>Password: <input type='text' name='WiFiPass' value='" + wifi_password + "'>"
  + "<br>Hidden: <input type='checkbox' name='WiFiHidden' value=" + wifi_hidden + ">"
  + "<br><input type='submit' value='Save'></p></form>";  
}

void setup(void){
  pinMode(LED_BUILTIN, OUTPUT); 
  Serial.begin(1200);
  SPIFFS.begin();
  loadConfig();
  
// Determine if set to Access point mode

  if (wifi_accesspointmode == 1) {
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(wifi_ssid, wifi_password, wifi_channel, wifi_hidden);
  }
  else if (wifi_accesspointmode != 1) {
    WiFi.config(local_IP, gateway, subnet);
    WiFi.begin(wifi_ssid, wifi_password);
  }

  server.on("/", [](){
    server.send(200, "text/html", HTML_CSS_STYLING + "<h1>WHID Injector</h1><p>WiFi HID Injector for Fun & Profit</p><p>-----------------------------------------------</span></p><a href=\"/uploadpayload\">Upload Payload</a><br>&nbsp;<br><a href=\"/listpayloads\">Choose Payload</a><br>&nbsp;<br><a href=\"/format\">Format File System</a><br>&nbsp;<br><a href=\"/config\">Configure</a><p>-----------------------------------------------</p>");
  });

  server.on("/config", [](){
    server.send(200, "text/html", HTML_CSS_STYLING + HTML_BACK_TO_INDEX + "<br>" + GetConfigForm());
  });
  
  server.on("/config/update", HTTP_POST, [](){
    int args = server.args();
    for (int i = 0; i < args; i++)
    {
      String key = server.argName(i);
      String value = server.arg(i);
      setValue(key, value);
    }
    writeConfig();
    server.send(200, "text/html", HTML_CSS_STYLING + HTML_BACK_TO_INDEX + "<h2>Update Successful!</h2>");
  });
  
  server.on("/format", [](){
    server.send(200, "text/html", HTML_CSS_STYLING + HTML_BACK_TO_INDEX + "<h2>This will reformat the SPIFFS File System.</h2><br><br><h2>You will delete all Payloads! Are you sure?</h2><br><br><a href=\"/format/yes\">YES</a> - <a href=\"/\">NO</a>");
  });

  server.on("/format/yes", [](){
    server.send(200, "text/html", HTML_CSS_STYLING + HTML_BACK_TO_INDEX + "<h2>Formatting file system: This may take up to 90 seconds</h2>");
    SPIFFS.format();
  });
    
  server.on("/uploadpayload", [](){
    server.send(200, "text/html", HTML_CSS_STYLING + HTML_BACK_TO_INDEX + "<b><h2>Upload Payload:</h2></b><br><br><form method='POST' action='/upload' enctype='multipart/form-data'><input type='file' name='upload'><input type='submit' value='Upload'></form>");
  });
    
  server.on("/listpayloads", ListPayloads);
    
  server.onFileUpload(handleFileUpload);
    
  server.on("/upload", HTTP_POST, [](){
    server.send(200, "text/html", HTML_CSS_STYLING + HTML_BACK_TO_INDEX + "<h2>Upload Successful!</h2><br><br><a href=\"/listpayloads\">List Payloads</a>");
  });

  server.on("/showpayload", [](){
    webString = "";
    String payload;
    payload += server.arg(0);
    File f = SPIFFS.open(payload, "r");
    String webString = f.readString();
    f.close();
    server.send(200, "text/html", HTML_CSS_STYLING + HTML_BACK_TO_INDEX + "<a href=\"/dopayload?payload="+payload+"\"><button>Run Payload</button></a><h2><pre>"+payload+"\n-----\n"+webString+"</pre></h2>");
    webString = "";
  });

  server.on("/dopayload", [](){
    String dopayload;
    dopayload += server.arg(0);
    server.send(200, "text/html", HTML_CSS_STYLING + HTML_BACK_TO_INDEX + "<pre><h3>Running payload: "+dopayload+"</h3></pre><br><h3>This may take a while to complete...</h3>");
    File f = SPIFFS.open(dopayload, "r");
    while(f.available()){
      String line = f.readStringUntil('\n');
      Serial.println(line);
      delay(DelayLength); //delay between lines in payload, I found running it slower works best
    }
    f.close();
  });
    
  server.begin();
}

void loop(){
  server.handleClient();
}
