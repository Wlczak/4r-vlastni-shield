#include "Menu.h"

void Menu::render()
{
    for (int i = 0; i < queueSize; i++)
    {
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
    for (int i = 0; i < queueSize; i++)
    {
        if (renderQueue[i] == 0)
        {
            renderQueue[i] = taskType;
            return i;
        }
    }
    return -1;
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
}