#include <Menu.h>

Menu menu;

int menuId = 0;
bool needToChangeMenu = true;
int incomingSerial;
String menuName = "Main menu";
String menuItems[] = { "thing1", "thing2", "thing3", "thing4" };

void setup() {
  Serial.begin(9600);

  menu.loadChars();
  // menu.debug();
  /* menu.loadingScreen();
  menu.typeOut(1, 0, "Welcome to:");
  menu.typeOut(1, 1, "V.corp. shield");
  delay(600);
  menu.clearArea();*/
}

void handleSerial() {
  incomingSerial = Serial.read();

  switch (incomingSerial) {
    case 49:  // left
      Serial.println("left");
      menuId = 1;
      needToChangeMenu = true;
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
    case 114:  // r
      break;
    default:
      Serial.print("undefined: ");
      Serial.println(incomingSerial);
  }
}

void loop() {
  if (Serial.available() > 0) {
    handleSerial();
  }
  if (needToChangeMenu) {
    switch (menuId) {
      case 0:
        menu.changeMenu(menuName, *menuItems);
        break;
      case 1:
        menu.changeMenu("left", *menuItems);
        break;
    }
    needToChangeMenu = false;
  }
}
