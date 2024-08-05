#include "Menu.h"

void Menu::render()
{
    for (int i = 0; i < queueSize; i++)
    {
        // cleans finished tasks
        if (renderFramesLeft[i] == 0)
        {
            renderQueue[i] = 0;
        }

        switch (renderQueue[i])
        {
        case 1:
            renderTypeOut(i);
            break;
        }
    }
}

int Menu::addTask(int taskType)
{
    int lastIndex = -1;
    for (int i = queueSize - 1; i >= 0; i--)
    {
        if (renderQueue[i] != 0)
        {
            lastIndex = i;
            break;
        }
    }

    // checks for out of boud errors
    int taskId = lastIndex + 1 < queueSize ? lastIndex + 1 : -1;

    if (taskId > -1)
    {
        renderQueue[taskId] = taskType;
    }
    return taskId;
}
int Menu::addTask(int taskType, int int1, int int2, String string1)
{
    int taskId = addTask(taskType);
    if (taskId >= 0)
    {
        renderInt[taskId][0] = int1;
        renderInt[taskId][1] = int2;
        renderString[taskId][0] = string1;
    }
    return taskId;
}

void Menu::renderTypeOut(int taskId)
{
    int &framesLeft = renderFramesLeft[taskId];
    int duration = renderDuration[taskId];
    int currentFrame = duration - framesLeft;
    int charIndex = currentFrame - 4; // -4 == first four frames
    long &delay = renderDelay[taskId][0];
    long &lastMillis = renderDelay[taskId][1];

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