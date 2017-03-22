/*
 * WHID Injector - ESP Sketch
 * http://whid.ninja
 * Forked by Luca Bongiorni
 * Based on ESPloit By www.Exploit.Agency / www.LegacySecurityGroup.com
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>


// ####################################
// ######## WiFi Configuration ########
// ####################################
const int accesspointmode = 1; // set to 0 to connect to an existing network or leave it set to 1 to use the esp8266 as an access point
const char ssid[] = "WHID-Injector";
const char password[] = "Vivalaf1g@";
const int channel = 6;
const int hidden = 0; // Set as 0 to broadcast AP's SSID or as 1 to hide SSID
// ####################################
// ######## WiFi Configuration ########
// ####################################


int DelayLength=2000; //Length of time in ms to wait between sending lines from payload
IPAddress local_IP(192,168,1,1); //IP of the esp8266 server
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
ESP8266WebServer server(80);
File fsUploadFile;
String webString;

void handleFileUpload()
{
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
  String FileList = "<style>body {background-color: #000000;}</style><a style=\"color: #00ff00;\" href=\"/\"><- BACK TO INDEX</a><br><br><h style=\"color: #00ff00;\"><b>Choose Payload:</b></h><br><br>";
  Dir dir = SPIFFS.openDir("/payloads");
  while (dir.next()) {
    String FileName = dir.fileName();
    File f = dir.openFile("r");
    FileList += " ";
    FileList += "<a style=\"color: #00ff00;\" href=\"/showpayload?payload="+FileName+"\">"+FileName+"</a>"+"<br>";
  }
  server.send(200, "text/html", FileList);
}

void setup(void)
{
  pinMode(LED_BUILTIN, OUTPUT); 
  Serial.begin(4800);
  SPIFFS.begin();
  
// Determine if set to Access point mode
  if (accesspointmode == 1) {
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ssid, password, channel, hidden);
  }
  else if (accesspointmode != 1) {
    WiFi.config(local_IP, gateway, subnet);
    WiFi.begin(ssid, password);
  }

  server.on("/", [](){
    server.send(200, "text/html", "<style>body {background-color: #000000;}.moveimage{position: relative;left: 55px;}</style><html><body><img class=\'moveimage\' src=\'data:image/png;base64,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\' /><h1 style=\"color: #00ff00;\">WHID Injector</h1><p><span style=\"color: #00ff00;\">WiFi HID Injector for Fun & Profit</span></p><p><span style=\"color: #00ff00;\">-----------------------------------------------</span></p><a style=\"color: #00ff00;\" href=\"/uploadpayload\">Upload Payload</a></html><br>-<br><a style=\"color: #00ff00;\" href=\"/listpayloads\">Choose Payload</a><br>-<br><a style=\"color: #00ff00;\" href=\"/format\">Format File System</a></html><p><span style=\"color: #00ff00;\">-----------------------------------------------</span></p>");
  });

  server.on("/format", [](){
    server.send(200, "text/html", "<style>body {background-color: #000000;}</style><html><body><h2 style=\"color: #00ff00;\">This will reformat the SPIFFS File System.</h2><br><br><h2 style=\"color: #00ff00;\">You will delete all Payloads! Are you sure?</h2><br><br><a style=\"color: #00ff00;\" href=\"/format/yes\">YES</a> - <a style=\"color: #00ff00;\" href=\"/\">NO</a></html></html>");
  });

  server.on("/format/yes", [](){
    server.send(200, "text/html", "<style>body {background-color: #000000;}</style><a style=\"color: #00ff00;\" href=\"/\"><- BACK TO INDEX</a><br><br><h2 style=\"color: #00ff00;\">Formatting file system: This may take up to 90 seconds</h2>");
    SPIFFS.format();
  });
    
  server.on("/uploadpayload", []() {
    server.send(200, "text/html", "<style>body {background-color: #000000;}</style><a style=\"color: #00ff00;\" href=\"/\"><- BACK TO INDEX</a><br><br><b><h2 style=\"color: #00ff00;\">Upload Payload:</h2></b><br><br><form method='POST' action='/upload' enctype='multipart/form-data'><input type='file' name='upload'><input type='submit' value='Upload'></form>");
  });
    
  server.on("/listpayloads", ListPayloads);
    
  server.onFileUpload(handleFileUpload);
    
  server.on("/upload", HTTP_POST, []() {
    server.send(200, "text/html", "<style>body {background-color: #000000;}</style><a style=\"color: #00ff00;\" href=\"/\"><- BACK TO INDEX</a><br><br><h2 style=\"color: #00ff00;\">Upload Successful!</h2><br><br><a style=\"color: #00ff00;\" href=\"/listpayloads\">List Payloads</a>");
  });

  server.on("/showpayload", [](){
    webString="";
    String payload;
    payload += server.arg(0);
    File f = SPIFFS.open(payload, "r");
    String webString = f.readString();
    f.close();
    server.send(200, "text/html", "<style>body {background-color: #000000;}</style><a style=\"color: #00ff00;\" href=\"/\"><- BACK TO INDEX</a><br><br><a style=\"color: #00ff00;\" href=\"/dopayload?payload="+payload+"\"><button>Run Payload</button></a><h2 style=\"color: #00ff00;\"><pre>"+payload+"\n-----\n"+webString+"</pre></h2>");
    webString="";
  });

  server.on("/dopayload", [](){
    String dopayload;
    dopayload += server.arg(0);
    server.send(200, "text/html", "<style>body {background-color: #000000;}</style><a style=\"color: #00ff00;\" href=\"/\"><- BACK TO INDEX</a><br><br><pre><h3 style=\"color: #00ff00;\">Running payload: "+dopayload+"</h3></pre><br><h3 style=\"color: #00ff00;\">This may take a while to complete...</h3>");
    File f = SPIFFS.open(dopayload, "r");
    while(f.available()) {
      String line = f.readStringUntil('\n');
      Serial.println(line);
      delay(DelayLength); //delay between lines in payload, I found running it slower works best
    }
    f.close();
  });
    
  server.begin();
}

void loop() {
  server.handleClient();
}
