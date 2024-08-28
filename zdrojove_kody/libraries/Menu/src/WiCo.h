#ifndef WiCo_h
#define WiCo_h

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

class WiCo
{
public:
    // initialization
    WiCo();

    // AP methods
    void startAP();
    void stopAP();
    String getAPIP();

    // webserver methods
    void startWebServer();
    void stopWebServer();
    void handleWebServer();

private:
    // settings setting methods
    void setAPsettings();

    // checking variables
    bool isAPActive = false;

    // AP settings
    int ap_max_devices;
    String ap_ssid;
    String ap_psk;
    int ap_ch;
    bool ap_hide_ssid;

    // web server
    ESP8266WebServer *server;

public:
    bool isWebserverRunning = false;
};

#endif
