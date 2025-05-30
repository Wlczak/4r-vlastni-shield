#include "Menu.h"

Menu::Menu(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t oneWirePin, uint8_t neopixelPin, uint8_t neopixelCount) : lcd(lcd_Addr, lcd_cols, lcd_rows), lcdChars(lcd), oneWire(oneWirePin), sensors(&oneWire), neopixel(neopixelCount, neopixelPin)
{
    sensors.begin();
    // display resolution
    cols = lcd_cols;
    rows = lcd_rows;

    lcd.init();
    lcd.setCursor(0, 0);
    lcd.backlight();
    lcd.clear();

    // default settings

    settings[0] = 0;
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

    digitalWrite(LED_B, HIGH);

    lcd.setCursor(6, 0);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);
    lcd.setCursor(1, 1);
    lcd.print("Vlasta's corp.");
    delay(1500);

    clearArea(0, 15, 1, 1, true);
    digitalWrite(LED_B, LOW);
    render();
    delay(100);
    digitalWrite(LED_B, HIGH);
    lcd.setCursor(3, 1);
    lcd.print("Loading");

    time = millis();
    mainTime = millis();
    digitalWrite(LED_B, LOW);
    delay(50);
    while (!finished)
    {
        if (millis() - time > 300)
        {
            digitalWrite(LED_B, LOW);
            if (dotCount >= 4)
            {
                clearArea(10, 12, 1, 1, true);
                render();
                dotCount = 1;
                digitalWrite(LED_B, HIGH);
                delay(50);
                digitalWrite(LED_B, LOW);
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
            digitalWrite(LED_B, HIGH);
        }
        delay(50);
        digitalWrite(LED_B, LOW);
    }
}
void Menu::clearArea(bool simultaneous)
{
    clearArea(0, cols, 0, 1, simultaneous);
}

void Menu::clearArea(int x1, int x2, int y1, int y2, bool simultaneous)
{
    int taskId = addTask(R_CLEAR_AREA, simultaneous, x1, x2, y1, y2);
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
        int taskId = addTask(R_TYPE_OUT, simultaneous, startX, startY, msg);
        if (taskId >= 0)
        {
            int frameCount = 4 + msg.length(); // 2x on and off + typing out + delete cursor (deletes on last frame)
            renderFramesLeft[taskId] = frameCount;
            renderDuration[taskId] = frameCount;
            renderInterval[taskId][0] = 250;
        }
    }
    else
    {
        error("string too long");
    }
}
void Menu::error(String msg)
{
    digitalWrite(LED_R, HIGH);
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(5, 0);
    lcd.print("Error");

    lcd.setCursor(0, 1);
    lcd.print(msg);
    delay(5000);
    digitalWrite(LED_R, LOW);
}

void Menu::startMenu(int menuId)
{
    int taskId;
    if (getFreeSlotsCount() >= 4) // check if menu animations fit in buffer
    {
        // menu structure set
        setMenuStructure(menuId);

        // menu select animations
        clearArea(false);
        /*  centerTypeOut(0, menuName, false);
          asynchDelay(340);
          clearArea(false);*/

        // selects propper execution based on menu type
        switch (menuType)
        {
        case S_NAVIGATION_MENU: // basic menu
            taskId = addTask(R_RENDER_MENU, false, menuId);
            if (taskId > -1)
            {
                renderFramesLeft[taskId] = 2;
                renderMenuItems = true;

                // reset scrolling for another menu

                menuScroll = 0;
                menuCursorScroll = 0;
                selectedItemIndex = 0;

                // checks if cursor is out of bounds

                if (menuScroll + 1 >= menuItemsLength)
                {
                    menuScroll = menuItemsLength - rows;
                }
                if (menuItemsLength <= rows - 1)
                {
                    menuCursorScroll = menuItemsLength - 1;
                    menuScroll = menuItemsLength - (rows - 1);
                }
                selectedItemIndex = menuScroll + menuCursorScroll;
            }
            break;
        case S_SENSOR_READOUT: // sensor readout
            taskId = addTask(R_RENDER_MENU, false, menuId);
            if (taskId > -1)
            {
                renderFramesLeft[taskId] = 2;
                // stuff after succesfully adding new task here:
            }
            break;

        case S_SETTINGS:
            taskId = addTask(R_RENDER_MENU, false, menuId);
            {
                renderFramesLeft[taskId] = 2;
                if (menuIncrement > 0)
                {
                    int currentValue = (settings[currentSettingIndex] - menuFirstValue) / menuIncrement;
                    if (settings[currentSettingIndex] == menuLastValue)
                    {
                        menuScroll = currentValue + 1;
                    }
                    else
                    {
                        menuScroll = currentValue;
                    }
                    /*int ceilValue = ceil(menuLastValue / menuIncrement) + 1;

                    if (currentValue < ceilValue)
                    {

                    }
                    else
                    {

                        menuScroll = ceilValue;
                    }*/
                }
                else
                {
                    menuScroll = settings[currentSettingIndex];
                }

                selectedItemIndex = 0;
            }
            break;
        }
    }
}

void Menu::asynchDelay(long time)
{
    int taskId = addTask(R_DELAY, false);

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

void Menu::synchClearArea(int x1, int x2, int y1, int y2)
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

void Menu::printMsg(int x, int y, String msg)
{
    if (x < cols && y < rows)
    {
        lcd.setCursor(x, y);
        if (msg.length() <= cols - x)
        {
            lcd.print(msg);
        }
        else
        {
            error("msg too long .-)");
        }
    }
    else
    {
        error("bad prt coords");
    }
}
void Menu::centerPrintMsg(int y, String msg)
{
    if (msg.length() <= cols)
    {
        printMsg(floor((cols - msg.length()) / 2), y, msg);
    }
    else
    {
        error("msg too long");
    }
}

void Menu::sleep()
{
    neopixel.blank();
    lcd.noBacklight();
}
void Menu::wakeUp()
{
    lcd.backlight();
}