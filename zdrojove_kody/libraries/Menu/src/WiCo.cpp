#include "WiCo.h"

WiCo::WiCo()
{
}

void WiCo::startAP()
{
    if (!isAPActive)
    {
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