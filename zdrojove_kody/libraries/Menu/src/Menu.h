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
  void centerTypeOut(int row, String msg);
  void typeOut(int startX, int startY, String msg);
  void changeMenu(String menuName, String &menuItems);

  // rendering engine methods

private:
  // object declaration
  LCDChars lcdChars;
  LiquidCrystal_I2C lcd;

  // default settings
  int cols = 16;
  int rows = 2;

  // engine variables
  String renderQueue[8];
  bool renderStatus[8];
  int renderInt[8][3];
  String renderString[8][1];

  // engine methods
  void render();
  void addTask(String taskType, int int1, int int2, String string1);
  void renderTypeOut();
};

#endif
