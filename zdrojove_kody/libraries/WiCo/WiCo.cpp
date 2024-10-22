#include "WiCo.h"

WiCo::WiCo()
{
}

void WiCo::startAP()
{
    if (!isAPActive)
    {
        WiFi.mode(WIFI_AP);
        setAPsettings();
        WiFi.softAP(ap_ssid, ap_psk, ap_ch, ap_hide_ssid, ap_max_devices);
        WiFi.softAPIP();
        isAPActive = true;
    }
}
void WiCo::stopAP()
{
    if (isAPActive)
    {
        WiFi.softAPdisconnect();
        isAPActive = false;
    }
}
String WiCo::getAPIP()
{
    return WiFi.softAPIP().toString();
}

void WiCo::connectSTA()
{
    Serial.println("connecting");
    if (!isSTAActive)
    {
        WiFi.mode(WIFI_STA);
        setSTAsettings();
        for (int i = 0; i < sta_ssid.size(); i++)
        {
            wifiMulti.addAP(sta_ssid.at(i), sta_psk.at(i));
        }
        for (int i = 0; i < 30; i++)
        {
            if (wifiMulti.run(sta_timeout) == WL_CONNECTED)
            {
                Serial.println("");
                Serial.print("WiFi connected: ");
                Serial.print(WiFi.SSID());
                Serial.print(" ");
                Serial.println(WiFi.localIP());
                break;
            }else{
                Serial.println("not connected");
            }
        }
        isSTAActive = true;
    }
}

void WiCo::disconnectSTA()
{
    if (isSTAActive)
    {
        WiFi.disconnect();
        isSTAActive = false;
    }
}