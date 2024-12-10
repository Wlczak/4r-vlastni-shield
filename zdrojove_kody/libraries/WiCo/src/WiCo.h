#ifndef WiCo_h
#define WiCo_h

#include <Arduino.h> // imports arduino stadard lib
#include <string>
#include <vector>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>

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
    void connectMQTT();
    static void handleInMQTT(char *topic, byte *payload, unsigned int length);
    void reconnectMQTT();
    void setupMQTT();
    void runMQTT();

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

    // MQTT stuff
    WiFiClient espClient;

    PubSubClient client;

    const char *mqtt_server = "10.202.31.167";

    unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
    char msg[MSG_BUFFER_SIZE];
    int value = 0;
};

#endif
