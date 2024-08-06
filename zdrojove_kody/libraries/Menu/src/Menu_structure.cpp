#include "Menu.h"

void Menu::setMenuStructure(int menuId)
{
    String name;
    String *tmp1;
    int *tmp2;

    delete[] menuItemNames;
    delete[] menuItemsLinks;

    switch (menuId)
    {
    case 1:
    {
        name = "Main menu";
        String tmp01[] = {
            "test1",
            "test2",
            "test3",
            "test4",
        };
        int tmp02[] = {1, 2, 3, 4, 5};

        tmp1 = tmp01;
        tmp2 = tmp02;
        break;
    }
    default:
    {
        String tmp01[] = {
            ""};
        int tmp02[] = {0};

        tmp1 = tmp01;
        tmp2 = tmp02;
        break;
    }
    }

    // debug
    for (int i = 0; i < 4; i++)
    {
        Serial.println(tmp1[i]);
    }

    if (name.length() <= cols)
    {
        if (sizeof(tmp1) == sizeof(tmp2))
        {
            int size = sizeof(tmp1);
            menuItemNames = new String[size];
            menuItemsLinks = new int[size];

            menuName = name;

            for (int i = 0; i < size; i++)
            {
                menuItemNames[i] = tmp1[i];
                menuItemsLinks[i] = tmp2[i];
            }
        }
        else
        {
            error("menu it.!=lengt");
        }
    }
    else
    {
        error("name too long");
    }
}