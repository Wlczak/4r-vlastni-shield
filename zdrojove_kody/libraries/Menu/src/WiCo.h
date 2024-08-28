#ifndef WiCo_h
#define WiCo_h

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

class WiCo
{
public:
    WiCo();
    void startAP();
    void stopAP();
    String getAPIP();

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
};

#endif
