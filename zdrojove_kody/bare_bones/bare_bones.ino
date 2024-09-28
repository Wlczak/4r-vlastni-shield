#include <Menu.h>
#include <WiCo.h>

#define re_sw D5
#define re_dt D6
#define re_clk D7

#define led_r D3
#define led_b D0


#define one_w_temp D4
#define neopixelPin D8
#define neopixelLeds 8

#define sleepAfterS 20


Menu menu(0x27, 16, 2, one_w_temp, neopixelPin, neopixelLeds);
WiCo WiCo();


int incomingSerial;
long fpsTime = millis();
long fpsCounter = 0;
bool showFps = false;

bool lastDt = digitalRead(re_dt);
bool lastClk = digitalRead(re_clk);
long debounceTime = millis();
long lastSwPress = millis();
long switchHold = -1;
long switchHoldTime = 400;
bool isSwitchPressed = false;
long lastActive = millis();
bool sleeping = false;

bool debug = false;

void wake_up() {
  lastActive = millis();
  if (sleeping) {
    menu.wakeUp();
    sleeping = false;
  }
}

void IRAM_ATTR handleRotation() {

  bool dt = digitalRead(re_dt);
  bool clk = digitalRead(re_clk);

  if (digitalRead(re_sw) == HIGH && millis() - debounceTime > 10) {
    wake_up();
    debounceTime = millis();

    bool dt = digitalRead(re_dt);
    bool clk = digitalRead(re_clk);

    if (dt == clk && lastDt == lastClk || dt == lastDt && clk != lastClk) {
      menu.inputUp();
      lastDt = digitalRead(re_dt);
      lastClk = digitalRead(re_clk);
    }
    if (dt != clk && lastDt != lastClk || dt == lastDt && clk != lastClk) {
      menu.inputDown();
      lastDt = digitalRead(re_dt);
      lastClk = digitalRead(re_clk);
    }
  }
}

void IRAM_ATTR handleSw() {
  if (millis() - lastSwPress > 500) {
    wake_up();
    if (digitalRead(re_sw) == HIGH) {

      if (millis() - switchHold < switchHoldTime) {
        menu.inputEnter();

      } else {
        menu.inputBack();
      }
      switchHold = -1;
      digitalWrite(led_b, LOW);
      isSwitchPressed = false;
    } else {
      switchHold = millis();
      isSwitchPressed = true;
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("");

  pinMode(re_sw, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(re_clk), handleRotation, CHANGE);
  attachInterrupt(digitalPinToInterrupt(re_sw), handleSw, CHANGE);

  pinMode(led_r, OUTPUT);
  pinMode(led_b, OUTPUT);

  menu.loadChars();

  menu.loadingScreen();
  menu.centerTypeOut(0, "V.corp. shield", false);
  menu.centerTypeOut(1, "v1.0.1", true);
  menu.asynchDelay(1000);
  menu.clearArea(false);

  menu.startMenu(1);
  digitalWrite(led_b, LOW);
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
      //menu.asynchDelay(5000);
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
      menu.sleep();
      sleeping = true;
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
  if (sleeping) {
    yield();
  } else {
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
    if (isSwitchPressed) {
      if (millis() - switchHold > switchHoldTime) {
        analogWrite(led_b, map(analogRead(A0), 0, 1023, 0, 255));
      }
      if (millis() - switchHold > 3000) {
        isSwitchPressed = false;
        digitalWrite(led_b, LOW);
        switchHold = -1;
      }
    }
    if (millis() - lastActive > sleepAfterS * 1000) {
      menu.sleep();
      sleeping = true;
    }
  }
}
