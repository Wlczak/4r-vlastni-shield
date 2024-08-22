#include "Menu.h"

void Menu::render()
{
    bool orderLevelHasMembers = false;
    for (int i = 0; i < queueSize; i++)
    {

        // cleans finished tasks
        if (renderFramesLeft[i] == 0)
        {
            renderQueue[i] = 0;
            renderOrder[i] = 0;
        }

        // selects current order level
        if (renderOrder[i] == 1)
        {
            orderLevelHasMembers = true;
            switch (renderQueue[i])
            {
            case 1:
                renderTypeOut(i);
                break;

            case 2:
                renderClearArea(i);
                break;

            case 3:
                renderDelay(i);
                break;

            case 4:
                renderMenu(i);
                break;
            }
        }
    }
    // if current animation order level is empty decrement other levels
    if (!orderLevelHasMembers)
    {
        for (int i = 0; i < queueSize; i++)
        {
            if (renderOrder[i] > 1)
            {
                renderOrder[i]--;
            }
        }
    }
}

int Menu::getMaxRenderOrder()
{
    int maxRenderOrder = 1;
    for (int orderMember : renderOrder)
    {
        if (orderMember > maxRenderOrder)
        {
            maxRenderOrder = orderMember;
        }
    }
    return maxRenderOrder;
}

int Menu::getFreeSlotsCount()
{
    int freeSlotsCount = 0;
    for (int queueMember : renderQueue)
    {
        if (queueMember == 0)
        {
            freeSlotsCount++;
        }
    }
    return freeSlotsCount;
}

int Menu::addTask(int taskType, bool simultaneous)
{
    for (int i = 0; i < queueSize; i++)
    {
        if (renderQueue[i] == 0)
        {
            renderOrder[i] = simultaneous ? getMaxRenderOrder() : getMaxRenderOrder() + 1;

            renderInterval[i][1] = millis();
            renderQueue[i] = taskType;
            return i;
        }
    }
    return -1;
}

int Menu::addTask(int taskType, bool simultaneous, int int1)
{
    int taskId = addTask(taskType, simultaneous);
    if (taskId >= 0)
    {
        renderInt[taskId][0] = int1;
    }
    return taskId;
}

int Menu::addTask(int taskType, bool simultaneous, int int1, int int2, String string1)
{
    int taskId = addTask(taskType, simultaneous);
    if (taskId >= 0)
    {
        renderInt[taskId][0] = int1;
        renderInt[taskId][1] = int2;
        renderString[taskId][0] = string1;
    }
    return taskId;
}

int Menu::addTask(int taskType, bool simultaneous, int int1, int int2, int int3, int int4)
{
    int taskId = addTask(taskType, simultaneous);
    if (taskId >= 0)
    {
        renderInt[taskId][0] = int1;
        renderInt[taskId][1] = int2;
        renderInt[taskId][2] = int3;
        renderInt[taskId][3] = int4;
    }
    return taskId;
}

void Menu::renderTypeOut(int taskId)
{
    int &framesLeft = renderFramesLeft[taskId];
    int duration = renderDuration[taskId];
    int currentFrame = duration - framesLeft;
    int charIndex = currentFrame - 4; // -4 == first four frames
    long &delay = renderInterval[taskId][0];
    long &lastMillis = renderInterval[taskId][1];

    int startX = renderInt[taskId][0];
    int startY = renderInt[taskId][1];
    String msg = renderString[taskId][0];

    if (millis() - lastMillis > delay)
    {
        lastMillis = millis();
        if (currentFrame < 4)
        {

            lcd.setCursor(startX, startY);
            if (currentFrame % 2 == 0)
            {
                lcd.write((char)255);
            }
            else
            {
                lcd.write((char)32);
            }
        }
        else
        {
            lcd.setCursor(startX + charIndex, startY);
            lcd.print(msg.charAt(charIndex));
            lcd.setCursor(startX + charIndex + 1, startY);
            lcd.write((char)255);
        }
        framesLeft--;
        if (framesLeft == 0)
        {
            lcd.setCursor(startX + charIndex + 1, startY);
            lcd.write((char)32);
        }
    }
}

void Menu::renderClearArea(int taskId)
{
    int x1 = renderInt[taskId][0];
    int x2 = renderInt[taskId][1];
    int y1 = renderInt[taskId][2];
    int y2 = renderInt[taskId][3];

    for (int x = x1; x <= x2; x++)
    {
        for (int y = y1; y <= y2; y++)
        {
            lcd.setCursor(x, y);
            lcd.print(" ");
        }
    }
    renderFramesLeft[taskId]--;
}

void Menu::renderDelay(int taskId)
{
    long &delay = renderInterval[taskId][0];
    long &lastMillis = renderInterval[taskId][1];

    if (renderFramesLeft[taskId] > 1)
    {
        lastMillis = millis();
        renderFramesLeft[taskId]--;
    }
    else
    {
        if (millis() - lastMillis > delay)
        {
            renderFramesLeft[taskId]--;
        }
    }
}

void Menu::renderMenu(int taskId)
{
    // variable declaration
    int cursorIndexX;
    int cursorIndexY;
    int &framesLeft = renderFramesLeft[taskId];
    long &lastMillis = renderInterval[taskId][1];
    int &lastDataLength = renderInt[taskId][0];
    String data;
    // changes menu rendering based on menu type
    switch (menuType)
    {
    case 1:
        cursorIndexX = menuItemNames[selectedItem].length() + 1;
        cursorIndexY = menuCursorScroll;

        if (renderMenuItems)
        {
            renderMenuItems = false;

            for (int i = 0; i < rows; i++)
            {
                int itemIndex = menuScroll + i;

                synchClearArea(0, cols - 1, i, i);
                if (itemIndex < menuItemsLength)
                {
                    lcd.setCursor(0, i);
                    lcd.print(menuItemNames[itemIndex]);
                }
            }
        }

        if (millis() - lastMillis > 690)
        {
            lastMillis = millis();

            if (framesLeft % 2 == 0)
            {
                lcd.setCursor(cursorIndexX, cursorIndexY);
                lcd.write(byte(0));
                framesLeft--;
            }
            else
            {
                lcd.setCursor(cursorIndexX, cursorIndexY);
                lcd.write(byte(1));
                framesLeft++;
            }
        }

        // input controlls
        if (inputBuffer != 0)
        {

            lastMillis = millis() + 1000;
            switch (inputBuffer)
            {
            case 1:
                if (selectedItem - 1 >= 0)
                {
                    lcd.setCursor(cursorIndexX, cursorIndexY);
                    lcd.print(" ");
                    selectedItem--;
                    if (selectedItem == menuScroll - 1 && menuScroll != 0)
                    {
                        menuScroll--;
                        renderMenuItems = true;
                    }
                    else
                    {
                        menuCursorScroll--;
                    }
                }
                break;

            case 2:
                if (selectedItem < menuItemsLength - 1) // -1 because of the difference sizeof starts at 1 while selectedItem starts at 0
                {

                    lcd.setCursor(cursorIndexX, cursorIndexY);
                    lcd.print(" ");
                    selectedItem++;
                    if (selectedItem > menuScroll + rows - 1)
                    {
                        menuScroll++;
                        renderMenuItems = true;
                    }
                    else
                    {
                        menuCursorScroll++;
                    }
                }
                break;

            case 3:
                bool historySaved;
                historySaved = false;

                for (int i = 0; i < 16; i++)
                {

                    if (menuHistory[i] == 0)
                    {
                        historySaved = true;
                        menuHistory[i] = renderInt[taskId][0];
                        break;
                    }
                }
                if (!historySaved)
                {
                    error("history !saved");
                }
                framesLeft = 0;

                startMenu(menuItemsLinks[selectedItem]);
                break;

            case 4:
                for (int i = queueSize - 1; i >= 0; i--)
                {

                    if (menuHistory[i] != 0)
                    {
                        framesLeft = 0;
                        startMenu(menuHistory[i]);
                        menuHistory[i] = 0;
                        break;
                    }
                }
                break;
            }
            inputBuffer = 0;
        }
        break;

    case 2: // menu type 2 - sensor readout
        if (framesLeft == 2)
        {
            synchClearArea(0, cols - 1, 0, rows - 1);
            centerPrintMsg(0, menuName);
            framesLeft--;
            lastMillis += 3000;
        }

        if (millis() - lastMillis > 3000)
        {
            data = readDeviceInput(deviceId);

            // checks to delete any characters that are not automatically overflowing
            if (data.length() != lastDataLength)
            {
                synchClearArea(lastDataLength - data.length(), lastDataLength, 1, 1);
            }

            lcd.setCursor(0, 1);

            lcd.print(data);
            lastDataLength = data.length();
            lastMillis = millis();
        }

        // input controlls
        if (inputBuffer != 0)
        {

            lastMillis = millis() + 1000;
            switch (inputBuffer)
            {
            case 4:
                for (int i = queueSize - 1; i >= 0; i--)
                {

                    if (menuHistory[i] != 0)
                    {
                        framesLeft = 0;
                        startMenu(menuHistory[i]);
                        menuHistory[i] = 0;
                        break;
                    }
                }
                break;
            }
            inputBuffer = 0;
        }
        break;

    case 3:
        if (framesLeft == 2)
        {
            synchClearArea(0, cols - 1, 0, rows - 1);
            centerPrintMsg(0, menuName);
            renderMenuItems = true;
            framesLeft--;
        }
        if (millis() - lastMillis > 1000 / 60)
        {

            if (selectedItem != menuScroll || renderMenuItems)
            {
                synchClearArea(0, cols - 1, 1, rows - 1);

                String selectedItemName = menuItemNames[menuScroll];
                int centerStart = floor((cols - selectedItemName.length()) / 2);

                for (int i = 0; i < cols; i++)
                {
                    String output = " ";
                    bool repeat = true;
                    int cumulativeLength = 0;
                    int indexOffset = 0;

                    if (i >= centerStart && i <= centerStart + selectedItemName.length() - 1)
                    {

                        output = selectedItemName.charAt(i - centerStart);
                    }
                    else if (i - centerStart + 2 >= 0 && centerStart + selectedItemName.length() + 2 > i)
                    {
                        if (i < centerStart) // bf selected string
                        {
                            output = i == centerStart - 1 ? "|" : " ";
                        }
                        else
                        {
                            output = i == centerStart + selectedItemName.length() ? "|" : " ";
                        }
                    }
                    else if (i < centerStart)
                    {

                        indexOffset--;

                        /*while (repeat)
                        {
                            if (menuItemsLength + indexOffset <= 0)
                            {
                                repeat = false;
                            }
                            String currentItem = menuItemNames[menuScroll + indexOffset];
                            if (currentItem.length() > centerStart - i - 2)
                            {

                                output = currentItem.charAt(currentItem.length() - 1 - centerStart + 2 + i);
                                repeat = false;
                            }
                            else
                            {
                                cumulativeLength += currentItem.length();
                                indexOffset--;
                            }
                        }*/
                        output = "/";
                    }

                    else
                    {
                        output = ":";
                    }

                    lcd.setCursor(i, 1);
                    lcd.print(output);
                }

                lcd.print("s;tt |haha| tt;s");

                lastMillis = millis();
                renderMenuItems = false;
                selectedItem = menuScroll;
            }
        }

        // input controlls
        if (inputBuffer != 0)
        {

            lastMillis = millis() + 1000;
            switch (inputBuffer)
            {
            case 1:
                if (menuScroll > 0)
                {
                    menuScroll--;
                }
                break;
            case 2:
                if (menuScroll < menuItemsLength - 1)
                {
                    menuScroll++;
                }
                break;
            case 4:
                for (int i = queueSize - 1; i >= 0; i--)
                {

                    if (menuHistory[i] != 0)
                    {
                        framesLeft = 0;
                        startMenu(menuHistory[i]);
                        menuHistory[i] = 0;
                        break;
                    }
                }
                break;
            }
            inputBuffer = 0;
        }

        break;
    }
}