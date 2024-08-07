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

  // modular frame by frame sytem
  void startMenu(int menuId);
  void centerTypeOut(int row, String msg, bool simultaneous);
  void typeOut(int startX, int startY, String msg, bool simultaneous);
  void asynchDelay(long time);

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
  int renderDuration[8];     // optional
  long renderInterval[8][2]; // [0] = delay in ms [1] = current millis()(set automatically)
  int renderInt[8][4];       // optional
  String renderString[8][1]; // optional

  // menu structure variables

  String menuName = "";
  int menuPage = 0;
  int selectedItem = 0;
  bool renderMenuItems = false;
  String *menuItemNames = new String[0];
  int *menuItemsLinks = new int[0];

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

public:
  // input methods
  void inputUp();
  void inputDown();
  void inputEnter();
  void inputBack();
};

#endif
