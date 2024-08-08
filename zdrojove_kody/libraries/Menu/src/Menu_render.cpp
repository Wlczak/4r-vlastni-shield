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
            Serial.print("render order: ");
            Serial.println(renderOrder[i]);
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

    int cursorIndexX = menuItemNames[selectedItem].length() + 1;
    int cursorIndexY = menuCursorScroll;
    int &framesLeft = renderFramesLeft[taskId];
    long &lastMillis = renderInterval[taskId][1];

    if (renderMenuItems)
    {
        renderMenuItems = false;

        for (int i = 0; i < rows; i++)
        {
            int itemIndex = menuScroll + i;

            synchClearArea(0, cols - 1, i, i);
            if (itemIndex < sizeof(menuItemNames))
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
    if (inputBuffer != 0)
    {
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
            if (selectedItem < sizeof(menuItemNames) - 1) // -1 because of the difference sizeof starts at 1 while selectedItem starts at 0
            {
                Serial.println("down");
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
        }
        inputBuffer = 0;
    }
}