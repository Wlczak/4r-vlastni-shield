#include <Menu.h>
Menu menu;
void setup() {
  // put your setup code here, to run once:
  menu.loadChars();
  // menu.debug();
  menu.loadingScreen();
  menu.typeOut(1, 0, "Welcome to:");
  menu.typeOut(1, 1, "V.corp. shield");
  delay(600);
  menu.clearArea();
  String text = "XXXXXXXXXXXXXXXX";
  menu.centerTypeOut(0, text);
}

void loop() {
}
