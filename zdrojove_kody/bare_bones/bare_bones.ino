#include <Menu.h>
Menu menu;
void setup() {
  // put your setup code here, to run once:
  menu.loadChars();
  // menu.debug();
  menu.loadingScreen();
  menu.typeOut(1, 0, "Typed out text");
  menu.typeOut(1, 0, "is really cool");
}

void loop() {
  // put your main code here, to run repeatedly:
}
