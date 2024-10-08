// LCDChars.h
#ifndef LCDChars_h
#define LCDChars_h

#include <Arduino.h> // imports arduino stadard lib
#include <LiquidCrystal_I2C.h>

class LCDChars
{
public:
  LCDChars(LiquidCrystal_I2C &lcd); // constructor with a LiquidCrystal_I2C object passed as a method
  void loadChars();                 // loads custom chars
  void writeAllChars();             // writes out all custom chars
  byte *getChar(int num);           // returns a byte * array of lines for custom character

private:
  LiquidCrystal_I2C &lcd; // lcd object
  byte character[8];      // variable to load custom characters to
};

#endif
