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
  void loadChars();
  void debug();
  void loadingScreen();
  void clearArea(int x1, int x2, int y1, int y2);
  void typeOut(int startX, int startY, String msg);
  void error(String msg);

private:
  LCDChars lcdChars;
  LiquidCrystal_I2C lcd;
};

#endif
