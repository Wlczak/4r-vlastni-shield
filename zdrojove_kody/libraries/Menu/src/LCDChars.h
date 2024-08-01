// LCDChars.h
#ifndef LCDChars_h
#define LCDChars_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LCDChars
{
public:
  LCDChars();
  void begin();
  void loadChars();
  byte *getChar(int num);

private:
  LiquidCrystal_I2C lcd;
  
  byte character[8];
};

#endif
