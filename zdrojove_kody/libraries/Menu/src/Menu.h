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
  void clearArea(bool simultaneous);
  void clearArea(int x1, int x2, int y1, int y2, bool simultaneous);

  // execute slowly - stops the whole code from executing
  void changeMenu(String menuName, String menuItems[]);

  // modular frame by frame sytem
  void centerTypeOut(int row, String msg, bool simultaneous);
  void typeOut(int startX, int startY, String msg, bool simultaneous);

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
  int renderOrder[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  // render parameters
  int renderFramesLeft[8];
  int renderDuration[8];
  long renderDelay[8][2];
  int renderInt[8][4];
  String renderString[8][1];

  // engine methods
  int addTask(int taskType, bool simultaneous);
  int addTask(int taskType, bool simultaneous, int int1, int int2, String string1);
  int addTask(int taskType, bool simultaneous, int int1, int int2, int int3, int int4);
  void renderTypeOut(int taskId);
  void renderClearArea(int taskId);
  int getMaxRenderOrder();
};

#endif
