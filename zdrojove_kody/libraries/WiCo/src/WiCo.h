#ifndef WiCo_h
#define WiCo_h

#include <Arduino.h> // imports arduino stadard lib
#include <string>
#include <vector>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <PubSubClient.h>

class WiCo
{
public:
    // initialization
    WiCo();

    // AP methods
    void startAP();
    void stopAP();
    String getAPIP();

    // STA connect methods
    void connectSTA();
    void disconnectSTA();
    void setSTAsettings();

    // webserver methods
    void startWebServer();
    void stopWebServer();
    void handleWebServer();
    void setWebStructure();

    // MQTT
    //void connectMQTT();
private:
    // settings setting methods
    void setAPsettings();

    // checking variables
    bool isAPActive = false;
    bool isSTAActive = false;

public:
    bool isWebserverRunning = false;

private:
    // AP settings
    int ap_max_devices;
    String ap_ssid;
    String ap_psk;
    int ap_ch;
    bool ap_hide_ssid;

    // STA settings
    int sta_timeout;
    std::vector<const char *> sta_ssid;
    std::vector<const char *> sta_psk;

    // STA class
    ESP8266WiFiMulti wifiMulti;

    // web server
    ESP8266WebServer *server;
};

#endif
