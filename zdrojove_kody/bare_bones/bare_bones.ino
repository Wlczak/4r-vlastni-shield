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
      menu.typeOut(1, 1, "left");
      break;
    case 50:  // down
      menu.typeOut(8, 1, "down");
      Serial.println("down");
      break;
    case 51:  // right
      menu.centerTypeOut(0, "right");
      Serial.println("right");
      break;
    case 53:  // up
      Serial.println("up");
      break;
    case 114:  // r
      break;
    case 102:  // f
      showFps = !showFps;
      break;
    case 100:  // d
      debug = !debug;
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
