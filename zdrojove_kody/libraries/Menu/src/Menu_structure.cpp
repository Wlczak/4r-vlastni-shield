#include "Menu.h"

void Menu::setMenuStructure(int menuId)
{
    String name;
    int type;
    String *tmp1;
    int *tmp2;
    int size1;
    int size2;
    programType = 0;

    delete[] menuItemNames;
    delete[] menuItemsLinks;

    switch (menuId)
    {
    case 1:
    {
        name = "Main menu";
        type = 1;
        static String tmp01[] = {
            "Temperature",
            "Light",
            "Settings",
            "Debug"};
        static int tmp02[] = {2, 3, 4, 5};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;
    }
    case 2:
    {
        name = "Temperature";
        type = 2;
        break;
    }
    case 4:
    {
        name = "Settings";
        type = 1;
        static String tmp01[] = {
            "Placeholder"};
        static int tmp02[] = {15};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;
    }
    case 5:
    {
        name = "Debug";
        type = 1;
        static String tmp01[] = {
            "Main menu",
            "short2",
            "veeery long3",
            "ha4",
            "yo5",
            "hello kelo to6"};
        static int tmp02[] = {1, 6515641, 34, 420, 59, 17};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;
    }
    default:
    {
        name = "Default";
        static String tmp01[] = {
            "Main menu"};
        static int tmp02[] = {1};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;
    }
    }

    if (name.length() <= cols)
    {
        menuName = name;
        menuType = type;

        if (type == 1) // perform checks only for standard menu
        {
            for (int i = 0; i < size1; i++)
            {
                if (tmp1[i].length() > cols - 2)
                {
                    error("menu it. t.long");
                }
            }

            if (size1 == size2)
            {
                int size = size1;
                menuItemNames = new String[size];
                menuItemsLinks = new int[size];
                menuItemsLength = size;

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
    }
    else
    {
        error("name too long");
    }
}