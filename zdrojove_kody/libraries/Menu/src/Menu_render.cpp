#include "Menu.h"

void Menu::render()
{
}

void Menu::addTask(String taskType, int int1, int int2, String string1)
{
    for (int i = 0; i < sizeof(renderQueue) / sizeof(renderQueue[0]); i++)
    {
        if (renderQueue[i] == "")
        {
            renderQueue[i] = taskType;
            break;
        }
        Serial.println(renderQueue[i]);
    }
}

void Menu::renderTypeOut()
{
}