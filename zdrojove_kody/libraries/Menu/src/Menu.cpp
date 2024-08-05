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
    delay(3000);
    lcd.clear();
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

    clearArea(0, 15, 1, 1, true);
    render();
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
                clearArea(10, 12, 1, 1, true);
                render();
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
void Menu::clearArea(bool simultaneous)
{
    clearArea(0, cols, 0, 1, simultaneous);
}

void Menu::clearArea(int x1, int x2, int y1, int y2, bool simultaneous)
{
    int taskId = addTask(2, simultaneous, x1, x2, y1, y2);
    if (taskId >= 0)
    {
        renderInt[taskId][0] = x1;
        renderInt[taskId][1] = x2;
        renderInt[taskId][2] = y1;
        renderInt[taskId][3] = y2;

        renderFramesLeft[taskId] = 1;
        renderInterval[taskId][0] = 0;
    }

    renderInt[8][4];
}

void Menu::centerTypeOut(int row, String msg, bool simultaneous)
{
    if (msg.length() <= cols)
    {
        typeOut(floor((cols - msg.length()) / 2), row, msg, simultaneous);
    }
    else
    {
        error("string too long");
    }
}

void Menu::typeOut(int startX, int startY, String msg, bool simultaneous)
{
    if (msg.length() <= cols - startX)
    {
        int taskId = addTask(1, simultaneous, startX, startY, msg);
        if (taskId >= 0)
        {
            int frameCount = 4 + msg.length(); // 2x on and off + typing out + delete cursor (deletes on last frame)
            renderFramesLeft[taskId] = frameCount;
            renderDuration[taskId] = frameCount;
            renderInterval[taskId][0] = 333;
        }
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
    delay(5000);
}

void Menu::changeMenu(String menuName, String menuItems[])
{
    clearArea(true);
    centerTypeOut(0, menuName, false);
    for (int i = 0; i < 4; i++)
    {
        Serial.println(menuItems[i]);
    }
}

void Menu::asynchDelay(long time)
{
    int taskId = addTask(3, false);

    if (time >= 0)
    {
        if (taskId > -1)
        {
            renderFramesLeft[taskId] = 2;
            renderInterval[taskId][0] = time;
        }
    }
    else
    {
        error("no negative time");
    }
}