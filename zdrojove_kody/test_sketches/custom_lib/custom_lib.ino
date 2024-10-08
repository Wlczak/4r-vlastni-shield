#include <LCDChars.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte test[8] = {
  B00000,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B11111
};

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  //lcd.print("hello");

  lcd.setCursor(0, 0);

  lcd.createChar(3, test);
  lcd.begin(16, 2);
  lcd.write(byte(3));
}

void loop() {
  // put your main code here, to run repeatedly:
}
