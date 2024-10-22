#include <WiCo.h>

WiCo WiCo;

void setup() {
  Serial.begin(115200);
  Serial.print("hi");
  WiCo.startAP();
}

void loop() {
}
