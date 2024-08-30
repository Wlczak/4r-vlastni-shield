#include "WiCo.h"

void WiCo::setAPsettings()
{
    ap_ssid = "ssid";
    ap_psk = "password";
    ap_ch = 6;
    ap_hide_ssid = false;
    ap_max_devices = 1;
}

void WiCo::setSTAsettings()
{
    sta_timeout = 5000; // in ms
    sta_ssid = {"ADAM-PC", "wemos", "PixelSpot"};
    sta_psk = {"12345678", "wemosD1R2", "0987654321"};

    if (sta_ssid.size() != sta_psk.size())
    {
        Serial.println("STA settings ssid and psk size doesnt match");
    }
}