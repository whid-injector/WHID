#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>
#include <EEPROM.h>
#include "data.h"

#include "Settings.h"

#define BAUD_RATE 9600
#define bufferSize 600
#define debug false

/* ============= CHANGE WIFI CREDENTIALS ============= */
const char *ssid = "WiFi Duck";
const char *password = "quackquack"; //min 8 chars
/* ============= ======================= ============= */

AsyncWebServer server(80);
FSInfo fs_info;

Settings settings;

bool shouldReboot = false;

//Web stuff
extern const uint8_t data_indexHTML[] PROGMEM;
extern const uint8_t data_updateHTML[] PROGMEM;
extern const uint8_t data_error404[] PROGMEM;
extern const uint8_t data_styleCSS[] PROGMEM;
extern const uint8_t data_functionsJS[] PROGMEM;
extern const uint8_t data_liveHTML[] PROGMEM;
extern const uint8_t data_infoHTML[] PROGMEM;
extern const uint8_t data_nomalizeCSS[] PROGMEM;
extern const uint8_t data_skeletonCSS[] PROGMEM;
extern const uint8_t data_license[] PROGMEM;
extern const uint8_t data_settingsHTML[] PROGMEM;
extern const uint8_t data_viewHTML[] PROGMEM;

extern String formatBytes(size_t bytes);

//Script stuff
bool runLine = false;
bool runScript = false;
File script;

uint8_t scriptBuffer[bufferSize];
uint8_t scriptLineBuffer[bufferSize];
int bc = 0; //buffer counter
int lc = 0; //line buffer counter


void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
  File f;
  
  if(!filename.startsWith("/")) filename = "/" + filename;
  
  if(!index) f = SPIFFS.open(filename, "w"); //create or trunicate file
  else f = SPIFFS.open(filename, "a"); //append to file (for chunked upload)
  
  if(debug) Serial.write(data, len);
  f.write(data, len);
  
  if(final){ //upload finished
	  if(debug) Serial.printf("UploadEnd: %s, %u B\n", filename.c_str(), index+len);
	  f.close();
  }
}

void send404(AsyncWebServerRequest *request){
  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", data_error404, sizeof(data_error404));
  request->send(response);
}

void sendToIndex(AsyncWebServerRequest *request){
  AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "");
  response->addHeader("Location","/");
  request->send(response);
}

void sendSettings(AsyncWebServerRequest *request) {
	AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", data_settingsHTML, sizeof(data_settingsHTML));
	request->send(response);
}

void setup() {
  
  Serial.begin(BAUD_RATE);
  delay(2000);
  if(debug) Serial.println("\nstarting...\nSSID: "+ (String)ssid +"\nPassword: "+ (String)password);

  EEPROM.begin(4096);
  SPIFFS.begin();

  settings.load();
  if(debug) settings.print();

  if(settings.autoExec) {
	  String _name = (String)settings.autostart;
	  script = SPIFFS.open("/" + _name, "r");
	  runScript = true;
	  runLine = true;
  }
  
  WiFi.mode(WIFI_STA);
  WiFi.softAP(settings.ssid, settings.password, settings.channel, settings.hidden);
  
  // ===== WebServer ==== //
  MDNS.addService("http","tcp",80);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
	  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", data_indexHTML, sizeof(data_indexHTML));
	  request->send(response);
  });
  server.on("/index.html", HTTP_GET, sendToIndex);

  server.on("/live.html", HTTP_GET, [](AsyncWebServerRequest *request) {
	  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", data_liveHTML, sizeof(data_liveHTML));
	  request->send(response);
  });

  server.on("/view.html", HTTP_GET, [](AsyncWebServerRequest *request) {
	  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", data_viewHTML, sizeof(data_viewHTML));
	  request->send(response);
  });

  server.on("license", HTTP_GET, [](AsyncWebServerRequest *request) {
	  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", data_license, sizeof(data_license));
	  request->send(response);
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
	  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css", data_styleCSS, sizeof(data_styleCSS));
	  request->send(response);
  });

  server.on("/normalize.css", HTTP_GET, [](AsyncWebServerRequest *request) {
	  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css", data_nomalizeCSS, sizeof(data_nomalizeCSS));
	  request->send(response);
  });

  server.on("/skeleton.css", HTTP_GET, [](AsyncWebServerRequest *request) {
	  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css", data_skeletonCSS, sizeof(data_skeletonCSS));
	  request->send(response);
  });

  server.on("/functions.js", HTTP_GET, [](AsyncWebServerRequest *request) {
	  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/javascript", data_functionsJS, sizeof(data_functionsJS));
	  request->send(response);
  });

  server.on("/info.html", HTTP_GET, [](AsyncWebServerRequest *request) {
	  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", data_infoHTML, sizeof(data_infoHTML));
	  request->send(response);
  });

  server.on("/settings.html", HTTP_GET, [](AsyncWebServerRequest *request) {
	  sendSettings(request);
  });

  server.on("/settings.html", HTTP_POST, [](AsyncWebServerRequest *request) {

	  if(request->hasArg("ssid")) {
		  String _ssid = request->arg("ssid");
		  settings.ssidLen = _ssid.length();
		  _ssid.toCharArray(settings.ssid, 32);
		  if(debug) Serial.println("new SSID = '"+_ssid+"'");
	  }
	  if(request->hasArg("pswd")) {
		  String _pswd = request->arg("pswd");
		  settings.passwordLen = _pswd.length();
		  _pswd.toCharArray(settings.password, 32);
		  if(debug) Serial.println("new password = '" + _pswd + "'");
	  }
	  if(request->hasArg("autostart")) {
		  String _autostart = request->arg("autostart");
		  settings.autostartLen = _autostart.length();
		  _autostart.toCharArray(settings.autostart, 32);
		  if(debug) Serial.println("new autostart = '" + _autostart + "'");
	  }
	  if(request->hasArg("ch")) settings.channel = request->arg("ch").toInt();
	  if(request->hasArg("hidden")) settings.hidden = true;
	  else settings.hidden = false;
	  if(request->hasArg("autoExec")) settings.autoExec = true;
	  else settings.autoExec = false;
	  
	  settings.save();
	  if(debug) settings.print();

	  sendSettings(request);
  });

  server.on("/settings.json", HTTP_GET, [](AsyncWebServerRequest *request) {
	  String output = "{";
	  output += "\"ssid\":\"" + (String)settings.ssid + "\",";
	  output += "\"password\":\"" + (String)settings.password + "\",";
	  output += "\"channel\":" + String((int)settings.channel) + ",";
	  output += "\"hidden\":" + String((int)settings.hidden) + ",";
	  output += "\"autoExec\":" + String((int)settings.autoExec) + ",";
	  output += "\"autostart\":\"" + (String)settings.autostart + "\"";
	  output += "}";
	  request->send(200, "text/json", output);
  });

  server.on("/list.json", HTTP_GET, [](AsyncWebServerRequest *request) {
	  SPIFFS.info(fs_info);
	  Dir dir = SPIFFS.openDir("");
	  String output;
	  output += "{";
	  output += "\"totalBytes\":" + (String)fs_info.totalBytes + ",";
	  output += "\"usedBytes\":" + (String)fs_info.usedBytes + ",";
	  output += "\"list\":[ ";
	  while(dir.next()) {
		  File entry = dir.openFile("r");
		  String filename = String(entry.name()).substring(1);
		  output += '{';
		  output += "\"n\":\"" + filename + "\",";//name
		  output += "\"s\":\"" + formatBytes(entry.size()) + "\"";//size 
		  output += "},";
		  entry.close();
	  }
	  output = output.substring(0, output.length() - 1);
	  output += "]}";
	  request->send(200, "text/json", output);
  });

  server.on("/script", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->hasArg("name")){
      String _name = request->arg("name");
      request->send(SPIFFS, "/"+_name, "text/plain");
    }else send404(request);
  });

  server.on("/run", HTTP_POST, [](AsyncWebServerRequest *request) {
	  if(request->hasArg("name")) {
		  String _name = request->arg("name");
		  script = SPIFFS.open("/" + _name, "r");
		  runScript = true;
		  runLine = true;
		  request->send(200, "text/plain", "true");
	  }
	  else if(request->hasArg("script")) {
		  Serial.println(request->arg("script"));
		  request->send(200, "text/plain", "true");
	  }
	  else send404(request);
  });

  server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
	  if(request->hasArg("name") && request->hasArg("script")) {
		  String _name = request->arg("name");
		  String _script = request->arg("script");
		  File f = SPIFFS.open("/" + _name, "w");
		  if(f) {
			  f.print(_script);
			  request->send(200, "text/plain", "true");
		  }
		  else request->send(200, "text/plain", "false");
	  }
	  else send404(request);
  });


  server.on("/delete", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->hasArg("name")){
      String _name = request->arg("name");
      SPIFFS.remove("/"+_name);
      request->send(200, "text/plain", "true");
    }else send404(request);
  });

  server.on("/rename", HTTP_GET, [](AsyncWebServerRequest *request) {
	  if(request->hasArg("name") && request->hasArg("newName")) {
		  String _name = request->arg("name");
		  String _newName = request->arg("newName");
		  SPIFFS.rename("/" + _name, "/" + _newName);
		  request->send(200, "text/plain", "true");
	  }
	  else send404(request);
  });

  server.on("/format", HTTP_GET, [](AsyncWebServerRequest *request){
    SPIFFS.format();
    request->send(200, "text/plain", "true");
    sendToIndex(request);
  });

  server.on("/upload", HTTP_POST, [](AsyncWebServerRequest *request){
    sendToIndex(request);
  }, handleUpload);
  
  server.onNotFound([](AsyncWebServerRequest *request){
    send404(request);
  });

  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request) {
	  AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "");
	  response->addHeader("Location", "/info.html");
	  request->send(response);
  });

  server.on("/restart", HTTP_GET, [](AsyncWebServerRequest *request) {
	  shouldReboot = true;
  });

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request) {
	  settings.reset();
	  request->send(200, "text/plain", "true");
	  sendToIndex(request);
  });

  //update
  server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request){
    shouldReboot = !Update.hasError();
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", shouldReboot?"OK":"FAIL");
    response->addHeader("Connection", "close");
    request->send(response);
  },[](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
    if(!index){
      if(debug) Serial.printf("Update Start: %s\n", filename.c_str());
      Update.runAsync(true);
      if(!Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000)){
		  if(debug) Update.printError(Serial);
      }
    }
    if(!Update.hasError()){
      if(Update.write(data, len) != len){
        Update.printError(Serial);
      }
    }
    if(final){
      if(Update.end(true)){
		if(debug) Serial.printf("Update Success: %uB\n", index+len);
      } else {
		if(debug) Update.printError(Serial);
      }
    }
  });
  
  server.begin();
  
  if(debug) Serial.println("started");
}

void sendBuffer(){
  for(int i=0;i<bc;i++) Serial.write((char)scriptBuffer[i]);
  runLine = false;
  bc = 0;
}

void addToBuffer(){
  if(bc + lc > bufferSize) sendBuffer();
  for(int i=0;i<lc;i++){
    scriptBuffer[bc] = scriptLineBuffer[i];
    bc++;
  }
  lc = 0;
}

void loop() {
  if(shouldReboot) ESP.restart();
  
  if(Serial.available()) {
    uint8_t answer = Serial.read();
    if(answer == 0x99) {
      if(debug) Serial.println("done");
      runLine = true;
	}
	else {
		String command = (char)answer + Serial.readStringUntil('\n');
		command.replace("\r", "");
		if(command == "reset") {
			settings.reset();
			shouldReboot = true;
		}
	}
  }

  if(runScript && runLine){
    if(script.available()){
      uint8_t nextChar = script.read();
	  if(debug) Serial.write(nextChar);
      scriptLineBuffer[lc] = nextChar;
      lc++;
      if(nextChar == 0x0D || lc == bufferSize) addToBuffer();
    }else{
      addToBuffer();
      if(bc > 0) sendBuffer();
      runScript = false;
      script.close();
    }
  }

}
