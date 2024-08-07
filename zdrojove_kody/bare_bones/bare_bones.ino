#include <Menu.h>

Menu menu;

int menuId = 0;
bool needToChangeMenu = true;
int incomingSerial;
String menuName = "Main menu";
String menuItems[] = { "thing1", "thing2", "thing3", "thing4" };
long fpsTime = millis();
long fpsCounter = 0;
bool showFps = false;

bool debug = false;

void setup() {
  Serial.begin(9600);

  menu.loadChars();

  /*menu.loadingScreen();
  menu.typeOut(1, 0, "Welcome to:", false);
  menu.typeOut(1, 1, "V.corp. shield", false);
  menu.asynchDelay(600);
  menu.clearArea(false);*/
}

void handleSerial() {
  incomingSerial = Serial.read();

  switch (incomingSerial) {
    case 49:  // left
      menu.inputBack();
      break;
    case 50:  // down
      menu.inputDown();
      break;
    case 51:  // right
      menu.inputEnter();
      break;
    case 53:  // up
      menu.inputUp();
      break;
    case 114:  // r
      menu.asynchDelay(5000);
      break;
    case 102:  // f
      showFps = !showFps;
      break;
    case 100:  // d
      debug = !debug;
      break;
    case 109:  // m
      menu.startMenu(1);
      break;
    case 110:  // n
      menu.startMenu(2);
      break;
    default:
      Serial.print("undefined: ");
      Serial.println(incomingSerial);
  }
}

void fps() {
  fpsCounter++;
  if (millis() - fpsTime > 1000) {
    // Serial.println(millis() - fpsTime);
    Serial.println(fpsCounter);
    fpsTime = millis();
    fpsCounter = 0;
  }
}

void loop() {
  if (Serial.available() > 0) {
    handleSerial();
  }
  menu.render();
  if (showFps) {
    fps();
  }
  if (debug) {
    menu.debug();
    debug = !debug;
  }
}