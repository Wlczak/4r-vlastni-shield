#include <Menu.h>

Menu menu;

int menuId = 0;
bool needToChangeMenu = true;
int incomingSerial;

void setup() {
  Serial.begin(9600);

  menu.loadChars();
  // menu.debug();
  /* menu.loadingScreen();
  menu.typeOut(1, 0, "Welcome to:");
  menu.typeOut(1, 1, "V.corp. shield");
  delay(600);
  menu.clearArea();*/

  // opens main menu
  menu.centerTypeOut(0, "Main menu");
  delay(500);
  menu.clearArea();
}

void handleSerial() {
  incomingSerial = Serial.read();

  switch (incomingSerial) {
    case 49:  // left
      Serial.println("left");
      break;
    case 50:  // down
      Serial.println("down");
      break;
    case 51:  // right
      Serial.println("right");
      break;
    case 53:  // up
      Serial.println("up");
      break;
    default:
      Serial.println("undefined");
  }
}

void loop() {
  if (Serial.available() > 0) {
    handleSerial();
  }
  if (needToChangeMenu) {
    switch (menuId) {
    }
  }
}
