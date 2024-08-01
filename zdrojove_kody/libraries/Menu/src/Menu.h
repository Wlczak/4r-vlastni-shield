#ifndef Menu_h
#define Menu_h

#include "LCDChars.h"

class Menu
{
public:
  Menu();
  void loadChars();

private:
  LCDChars lcdChars;
};

#endif
