#ifndef Menu_h
#define Menu_h

#include "LCDChars.h"

class Menu
{
public:
  Menu();
  void loadChars();
  void debug();
  void loadingScreen();

private:
  LCDChars lcdChars;
  LiquidCrystal_I2C lcd;
};

#endif
