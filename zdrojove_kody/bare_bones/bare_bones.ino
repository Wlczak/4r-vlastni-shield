#include <Menu.h>
Menu menu;
void setup() {
  // put your setup code here, to run once:
  menu.loadChars();
  // menu.debug();
  menu.loadingScreen();
  menu.typeOut(0, 0, "Typed out text");
}

void loop() {
  // put your main code here, to run repeatedly:
}
