#include "Menu.h"

Menu::Menu() : lcd(0x27, 16, 2), lcdChars(lcd)
{
    lcd.init();
    lcd.setCursor(0, 0);
    lcd.backlight();
    lcd.clear();
}
void Menu::loadChars()
{
    lcdChars.loadChars();
};

void Menu::debug()
{
    lcdChars.writeAllChars();
};

void Menu::loadingScreen()
{
    lcd.setCursor(6, 0);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);
    lcd.setCursor(1, 1);
    lcd.print("Vlasta's corp.");
}