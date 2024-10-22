#include <WiCo.h>

WiCo wifi;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  wifi.setSTAsettings();
  wifi.connectSTA();
}

void loop() {
}
