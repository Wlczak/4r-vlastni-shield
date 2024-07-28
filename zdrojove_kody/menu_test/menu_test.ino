#include <LiquidCrystal_I2C.h>
#include <wifi_auth.h>
//#include <Menu.h>

//Menu menu;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
lcd.init();
lcd.clear();
lcd.backlight();
lcd.print("-/\\-");
}

void loop() {
  // put your main code here, to run repeatedly:

}
