#ifndef Menu_h
#define Menu_h

#include "LCDChars.h"

#include <cmath> // i dont think this needs to be here but am afraid that if I touch anything it will just fall like a house of cars -_-

#include <Arduino.h> // imports arduino stadard lib
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <RGB.h>

// define preprocessor macros

// for render function types

#define R_TYPE_OUT 1
#define R_CLEAR_AREA 2
#define R_DELAY 3
#define R_RENDER_MENU 4

// for structure types

#define S_DEFAULT 0;
#define S_NAVIGATION_MENU 1
#define S_SENSOR_READOUT 2
#define S_SETTINGS 3

// for settings id

#define SET_SHOW_CURSOR 0
#define SET_DEBUG_LED 1
#define SET_NEOPIXEL_EFFECT 2
#define SET_NEOPIXEL_BRIGHTNESS 3

// for input tags

#define IN_UP 1
#define IN_DOWN 2
#define IN_ENTER 3
#define IN_BACK 4

// debug leds

#define LED_B D0
#define LED_R D3

class Menu
{
public:
  Menu(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t oneWirePin, uint8_t neopixelPin, uint8_t neopixelCount); // counstructor that assigns all class level objects

  // execute slowly, works like intended
  void loadChars();       // loads custom characters
  void debug();           // shows custChar debug screen
  void loadingScreen();   // shows animated loading screen
  void error(String msg); // prints error with red led flash

  // execute in single frame - fast enough to use anywhere in code
  void clearArea(bool simultaneous);                                 // clears whole screen
  void clearArea(int x1, int x2, int y1, int y2, bool simultaneous); // clears specified area & queued

  // simple lcd print helper methods
  void synchClearArea(int x1, int x2, int y1, int y2); // clears specified area
  void printMsg(int x, int y, String msg);             // prints msg on specific coords & checks if can be printed
  void centerPrintMsg(int y, String msg);              // prints centered msg on specific coords & checks if can be printed

  // execute slowly - stops the whole code from executing // Wrong turn? You look lost, stranger.

  // modular frame by frame sytem
  void startMenu(int menuId);                                          // starts menu process by id
  void centerTypeOut(int row, String msg, bool simultaneous);          // centered type out animation
  void typeOut(int startX, int startY, String msg, bool simultaneous); // type out animation
  void asynchDelay(long time);                                         // adds delay as a queueble item

  // rendering engine methods
  void render(); // render every render task

  // puts the display to sleep mode
  void sleep();  // sleep
  void wakeUp(); // wake up

private:
  // object declaration
  LCDChars lcdChars;
  LiquidCrystal_I2C lcd;
  OneWire oneWire;
  DallasTemperature sensors;
  RGB neopixel;

  // default settings
  int cols;
  int rows;

  // engine variables
  int queueSize = 16;
  int renderQueue[16] = {0};
  int renderOrder[16] = {0};

  // render parameters
  int renderFramesLeft[16];
  int renderDuration[16];     // optional
  long renderInterval[16][2]; // [0] = delay in ms [1] = current millis()(set automatically)
  int renderInt[16][4];       // optional
  String renderString[16][1]; // optional

  // menu structure variables

  int programType = 0;
  int deviceId = 0;

  String menuName = "";
  int menuType = 0;
  int menuScroll = 0;
  int menuCursorScroll = 0;
  int selectedItemIndex = 0;
  bool renderMenuItems = false;
  String *menuItemNames = new String[0];
  int *menuItemsLinks = new int[0];
  int menuItemsLength = 0;
  int menuHistory[16] = {0};
  int menuFirstValue = -1;
  int menuLastValue = -1;
  int menuIncrement = -1;

  // settings variables
  int currentSettingIndex = -1;
  int settingSlots = 16;
  int settings[16];

  // engine methods
  int addTask(int taskType, bool simultaneous);
  int addTask(int taskType, bool simultaneous, int int1);
  int addTask(int taskType, bool simultaneous, int int1, int int2, String string1);
  int addTask(int taskType, bool simultaneous, int int1, int int2, int int3, int int4);
  void renderTypeOut(int taskId);
  void renderClearArea(int taskId);
  void renderDelay(int taskId);
  void renderMenu(int taskId);

  // other engine methods
  int getMaxRenderOrder();
  int getFreeSlotsCount();

  // menu structure setter
  void setMenuStructure(int menuId);

  // input variables
  int inputBuffer = 0;

  long led_millis;

public:
  // input methods
  void inputUp();
  void inputDown();
  void inputEnter();
  void inputBack();

private:
  String readDeviceInput(int deviceId);
};

#endif
