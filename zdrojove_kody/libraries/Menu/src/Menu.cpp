#include "Menu.h"

Menu::Menu() : lcd(0x27, cols, 2), lcdChars(lcd)
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
    delay(120000);
}

void Menu::loadingScreen()
{
    bool finished = false;
    int dotCount = 1;
    long mainTime;
    long time;

    lcd.setCursor(6, 0);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);
    lcd.setCursor(1, 1);
    lcd.print("Vlasta's corp.");
    delay(1500);

    clearArea(0, 15, 1, 1);
    lcd.setCursor(3, 1);
    lcd.print("Loading");

    time = millis();
    mainTime = millis();

    while (!finished)
    {
        if (millis() - time > 300)
        {
            if (dotCount >= 4)
            {
                clearArea(10, 12, 1, 1);
                dotCount = 1;
            }

            lcd.setCursor((9 + dotCount), 1);
            lcd.print(".");

            dotCount++;
            time = millis();
        }
        if (millis() - mainTime > 3000)
        {
            finished = true;
            lcd.clear();
        }
        delay(50);
    }
}
void Menu::clearArea()
{
    clearArea(0, cols, 0, 1);
}

void Menu::clearArea(int x1, int x2, int y1, int y2)
{
    for (int x = x1; x <= x2; x++)
    {
        for (int y = y1; y <= y2; y++)
        {
            lcd.setCursor(x, y);
            lcd.print(" ");
        }
    }
}

void Menu::centerTypeOut(int row, String msg)
{
    if (msg.length() <= cols)
    {
        typeOut(floor((cols - msg.length()) / 2), row, msg);
    }
    else
    {
        error("string too long");
    }
}

void Menu::typeOut(int startX, int startY, String msg)
{
    if (msg.length() <= cols - startX)
    {
        addTask("typeOut", startX, startY, msg);
    }
    else
    {
        error("string too long");
    }
}
void Menu::error(String msg)
{
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(5, 0);
    lcd.print("Error");

    lcd.setCursor(0, 1);
    lcd.print(msg);
    delay(120000);
}

void Menu::changeMenu(String menuName, String &menuItems)
{
    clearArea();
    centerTypeOut(0, menuName);
}