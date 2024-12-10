#include <WiCo.h>

WiCo WiCo;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  WiCo.setSTAsettings();
  WiCo.connectSTA();
  WiCo.connectMQTT();
  WiCo.setupMQTT();
}

void loop() {
  WiCo.runMQTT();
  delay(1000);
}
