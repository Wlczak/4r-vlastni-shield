// LCDChars.h
#ifndef LCDChars_h
#define LCDChars_h

#include <cstdint>

typedef uint8_t byte;

class LCDChars
{
public:
  LCDChars();
  //void loadChars();
  byte *getChar(int num);

private:
  int _num; // Private variable to store the pin number
  byte character[8];
};

#endif
