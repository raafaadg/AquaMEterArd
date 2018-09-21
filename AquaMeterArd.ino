#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

ESP8266WebServer server(80);
void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("RAIFF ESP");
 

  server.on ( "/aqua/1", []() {
    server.send ( 200, "application/json", "{\n \"time\": \"02:41:48 PM\",\n \"milliseconds_since_epoch\": 1525876908085,\n \"date\": \"05-09-2018\"\n}" );
  } );
  server.on("/aqua/liga", liga); 
  server.on("/aqua/des", des); 
  server.onNotFound(handleNotFound);
  
  server.begin();

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
  ArduinoOTA.handle();
  
  if(Serial.available()>0){
    String conteudo = "";
    char caractere;
    while(Serial.available() > 0) {
      caractere = Serial.read();
      if (caractere != '\n'){
        conteudo.concat(caractere);
      }
      delay(10);       
    }
    server.send(200,"text/plain",conteudo);
  }
  
}
void liga(){
  Serial.print("liga");
  server.send(200,"text/plain","liga");
}void des(){
  Serial.print("des");
  //server.send(200,"text/plain","desliga");
}
void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
