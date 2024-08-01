#include "LCDChars.h"

LCDChars::LCDChars() : lcd(0x27, 16, 2)
{
  Serial.begin(9600);
  begin();
}

void LCDChars::begin()
{
  lcd.init();
  lcd.setCursor(0, 0);
  // lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
}

void LCDChars::loadChars()
{

  byte *tmp;
  byte charMap[8];
  for (int i = 0; i < 8; i++)
  {
    tmp = getChar(i);
    for (int j = 0; j < 8; j++)
    {
      charMap[j] = tmp[j];
    }
    lcd.createChar(i, charMap);
    lcd.setCursor(i, 0);
    lcd.write(byte(i));
  }
  // lcd.clear();
}

byte *LCDChars::getChar(int num)
{

  _num = num;
  // byte character[8];
  switch (num)
  {
  case 0:
    character[0] = 0b00000;
    character[1] = 0b00110;
    character[2] = 0b01100;
    character[3] = 0b10000;
    character[4] = 0b11111;
    character[5] = 0b10000;
    character[6] = 0b01100;
    character[7] = 0b00110;
    break;
  case 1:
    character[0] = 0b00000;
    character[1] = 0b00000;
    character[2] = 0b00110;
    character[3] = 0b01000;
    character[4] = 0b11111;
    character[5] = 0b01000;
    character[6] = 0b00110;
    character[7] = 0b00000;
    break;
  case 2:
    character[0] = 0b00000;
    character[1] = 0b00000;
    character[2] = 0b00100;
    character[3] = 0b01000;
    character[4] = 0b11111;
    character[5] = 0b01000;
    character[6] = 0b00100;
    character[7] = 0b00000;
    break;
  case 3:
    character[0] = 0b11111;
    character[1] = 0b11111;
    character[2] = 0b11011;
    character[3] = 0b10111;
    character[4] = 0b00000;
    character[5] = 0b10111;
    character[6] = 0b11011;
    character[7] = 0b11111;

    break;
  case 4:
    character[0] = 0b10001;
    character[1] = 0b00000;
    character[2] = 0b00000;
    character[3] = 0b00000;
    character[4] = 0b11000;
    character[5] = 0b00000;
    character[6] = 0b11111;
    character[7] = 0b10001;
    break;
  case 5:
    character[0] = 0b10001;
    character[1] = 0b11111;
    character[2] = 0b00000;
    character[3] = 0b00000;
    character[4] = 0b00110;
    character[5] = 0b00000;
    character[6] = 0b00000;
    character[7] = 0b10001;
    break;
  case 6:
    character[0] = 0b10001;
    character[1] = 0b11110;
    character[2] = 0b00000;
    character[3] = 0b01110;
    character[4] = 0b11111;
    character[5] = 0b11111;
    character[6] = 0b00000;
    character[7] = 0b10001;
    break;
  case 7:
    character[0] = 0b10001;
    character[1] = 0b01010;
    character[2] = 0b01010;
    character[3] = 0b00100;
    character[4] = 0b00100;
    character[5] = 0b01010;
    character[6] = 0b01010;
    character[7] = 0b10001;
    break;
  default:
    for (int i = 0; i < 8; ++i)
    {
      character[i] = 0b00000;
    }
    break;
  }
  return character;
}
