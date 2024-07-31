// LCDChars.h
#ifndef LCDChars_h
#define LCDChars_h

#include <Arduino.h>
#include <LCDI2C_Katakana_Symbols.h>

class LCDChars
{
public:
  LCDChars();
  void begin();
  void loadChars();
  byte *getChar(int num);

private:
  LCDI2C_Katakana_Symbols lcd;  
  int _num; // Private variable to store the pin number
  byte character[8];
};

#endif
