#include <LiquidCrystal_I2C.h>
#include <wifi_auth.h>
#include <Menu.h>

Menu menu;
LiquidCrystal_I2C lcd(0x27, 16, 2);



void setup() {
  byte vc1[] = {
    B01010,
    B01010,
    B01010,
    B00100,
    B11111,
    B00000,
    B00000,
    B00000
  };
  byte vc2[] = {
    B00010,
    B00010,
    B00101,
    B00101,
    B10100,
    B10100,
    B01000, 
    B01000
  };
  byte vc3[] = {
    B00000,
    B00000,
    B00000,
    B11111,
    B00110,
    B01000,
    B01000, 
    B00110
  };
  // put your setup code here, to run once:
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.createChar(0, vc1);
  lcd.createChar(1, vc2);
  lcd.createChar(3, vc3);
  lcd.createChar(4, vc3);

  lcd.setCursor(6, 0);
  lcd.write(0);
  lcd.write(1);
  lcd.write(3);
  lcd.setCursor(1,1);
  lcd.print("Vlasta's corp.");
}

void loop() {
  // put your main code here, to run repeatedly:
}
