#include <WiCo.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

WiCo wico;
//WiFiEventHandler wifiEventHandler;




void setup() {
  // put your setup code here, to run once:

  Serial.begin(300);
  wico.startAP();


  //wifiEventHandler = WiFi.onSoftAPModeStationConnected(wico.test);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(wico.getAPIP());
}
