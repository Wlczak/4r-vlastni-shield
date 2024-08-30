#include <WiCo.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

WiCo wico;
//WiFiEventHandler wifiEventHandler;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  wico.connectSTA();
  wico.startWebServer();
  wico.setWebStructure();
  //wifiEventHandler = WiFi.onSoftAPModeStationConnected(wico.test);
}

void loop() {
  if (wico.isWebserverRunning) {
    wico.handleWebServer();
  }
}
