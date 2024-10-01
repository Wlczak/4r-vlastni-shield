#include <Menu.h>

// rotation encoder pins
#define re_sw D5
#define re_dt D6
#define re_clk D7

// debug leds pins
#define led_r D3
#define led_b D0

// Dallas instrument pin
#define one_w_temp D4

// Neopixel variables
#define neopixelPin D8
#define neopixelLeds 8

// automatic sleep timeout
#define sleepAfterS 120

// initialization of Menu object
Menu Menu(0x27, 16, 2, one_w_temp, neopixelPin, neopixelLeds);

// stores incoming serial input
int incomingSerial;

// fps counter releated variables
long fpsTime = millis();
long fpsCounter = 0;
bool showFps = false;

// rotary encoder related variables
bool lastDt = digitalRead(re_dt);
bool lastClk = digitalRead(re_clk);
long debounceTime = millis();
long lastSwPress = millis();
long switchHold = -1;
long switchHoldTime = 400;
bool isSwitchPressed = false;
long lastActive = millis();
bool sleeping = false;

// custom LCD characters debug screen
bool debug = false;

// method for handling screen wake up
void wake_up() {
  lastActive = millis();
  if (sleeping) {
    Menu.wakeUp();
    sleeping = false;
  }
}

// handles rotary encoder rotation
void IRAM_ATTR handleRotation() {

  bool dt = digitalRead(re_dt);
  bool clk = digitalRead(re_clk);

  if (digitalRead(re_sw) == HIGH && millis() - debounceTime > 10) {
    wake_up();
    debounceTime = millis();

    bool dt = digitalRead(re_dt);
    bool clk = digitalRead(re_clk);

    if (dt == clk && lastDt == lastClk || dt == lastDt && clk != lastClk) {
      Menu.inputUp();
      lastDt = digitalRead(re_dt);
      lastClk = digitalRead(re_clk);
    }
    if (dt != clk && lastDt != lastClk || dt == lastDt && clk != lastClk) {
      Menu.inputDown();
      lastDt = digitalRead(re_dt);
      lastClk = digitalRead(re_clk);
    }
  }
}

// handles rotary encoder switch
void IRAM_ATTR handleSw() {
  if (millis() - lastSwPress > 500) {
    wake_up();
    if (digitalRead(re_sw) == HIGH) {

      if (millis() - switchHold < switchHoldTime) {
        Menu.inputEnter();

      } else {
        Menu.inputBack();
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

  Menu.loadChars();

  Menu.loadingScreen();
  Menu.centerTypeOut(0, "V.corp. shield", false);
  Menu.centerTypeOut(1, "v1.0.1", true);
  Menu.asynchDelay(1000);
  Menu.clearArea(false);

  Menu.startMenu(1);
  digitalWrite(led_b, LOW);
}

// handling of serial input for debugging purposes
void handleSerial() {
  incomingSerial = Serial.read();

  switch (incomingSerial) {
    case 49:  // left
      Menu.inputBack();
      break;
    case 50:  // down
      Menu.inputDown();
      break;
    case 51:  // right
      Menu.inputEnter();
      break;
    case 53:  // up
      Menu.inputUp();
      break;
    case 114:  // r
      //Menu.asynchDelay(5000);
      break;
    case 102:  // f
      showFps = !showFps;
      break;
    case 100:  // d
      debug = !debug;
      break;
    case 109:  // m
      Menu.startMenu(1);
      break;
    case 110:  // n
      Menu.sleep();
      sleeping = true;
      break;
    default:
      Serial.print("undefined: ");
      Serial.println(incomingSerial);
  }
}

// fps counter
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
    yield();  // gives time to process backend processes like Wi-Fi connections
  } else {
    if (Serial.available() > 0) {
      handleSerial();
    }
    Menu.render(); // main rendering method, handles everything on the LCD
    if (showFps) {
      fps(); // returns fps count with serial
    }
    if (debug) { // prints LCD custom characters debug screen
      Menu.debug();
      debug = !debug;
    }
    if (isSwitchPressed) {
      if (millis() - switchHold > switchHoldTime) {
        analogWrite(led_b, map(analogRead(A0), 0, 1023, 0, 255)); // lights up blue LED if switch pressed for hold time
      }
      if (millis() - switchHold > 3000) {
        isSwitchPressed = false;
        digitalWrite(led_b, LOW);
        switchHold = -1;
      }
    }
    if (millis() - lastActive > sleepAfterS * 1000) { // starts sleep mode if inactive
      Menu.sleep();
      sleeping = true;
    }
  }
}
