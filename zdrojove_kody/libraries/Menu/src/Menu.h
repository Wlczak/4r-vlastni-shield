#ifndef Menu_h
#define Menu_h

#include "LCDChars.h"

#include <cmath>

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Menu
{
public:
  Menu();

  // execute slowly, works like intended
  void loadChars();
  void debug();
  void loadingScreen();
  void error(String msg);

  // execute in single frame - fast enough to use anywhere in code
  void clearArea();
  void clearArea(int x1, int x2, int y1, int y2);

  // execute slowly - stops the whole code from executing
  void changeMenu(String menuName, String &menuItems);
  
  // modular frame by frame sytem
  void centerTypeOut(int row, String msg);
  void typeOut(int startX, int startY, String msg);



  // rendering engine methods
  void render();

private:
  // object declaration
  LCDChars lcdChars;
  LiquidCrystal_I2C lcd;

  // default settings
  int cols = 16;
  int rows = 2;

  // engine variables
  int queueSize = 8;
  int renderQueue[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  // render parameters
  int renderFramesLeft[8];
  int renderDuration[8];
  long renderDelay[8][2];
  int renderInt[8][2];
  String renderString[8][1];

  // engine methods
  int addTask(int taskType);
  int addTask(int taskType, int int1, int int2, String string1);
  void renderTypeOut(int taskId);
};

#endif
