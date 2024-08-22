#include "Menu.h"

void Menu::setMenuStructure(int menuId)
{
    String name;
    int type;
    String *tmp1;
    int *tmp2;
    int size1;
    int size2;
    bool isRange = false;

    programType = 0;
    if (menuItemNames != nullptr && menuItemsLinks != nullptr)
    {
        delete[] menuItemNames;
        delete[] menuItemsLinks;
        menuItemNames = nullptr;
        menuItemsLinks = nullptr;
    }
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
        name = "DS18B20";
        type = 2;
        deviceId = 1;
        break;
    }
    case 3:
    {
        name = "photo";
        type = 2;
        deviceId = 2;
        break;
    }
    case 4:
    {
        name = "Settings";
        type = 1;
        static String tmp01[] = {
            "Cursor", "range test"};
        static int tmp02[] = {41, 42};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;
    }

    case 41:
        name = "Cursor";
        type = 3; // select menu
        isRange = false;

        static String tmp01[] = {
            "1", "12", "123", "1234", "12345", "123456", "1234567", "12345678", "123456789", "1234567891", "12345678912", "123456789123", "1234567891234", "12345678912345"};
        static int tmp02[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;

    case 42:
        name = "Range";
        type = 3; // select menu
        isRange = true;

        // range size
        size1 = 0;
        size2 = 10;

        break;
    case 5:
    {
        name = "Debug menu";
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
        type = 1;
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

        if (type == 1 || type == 3) // perform checks only for standard menu and setting select
        {
            if (!isRange)
            {
                for (int i = 0; i < size1; i++)
                {
                    if (tmp1[i].length() > cols - 2)
                    {
                        error("menu" + (String)i + "it. t.long");
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
            else if (size1 < size2)
            {
                int size = size2 - size1 + 1;
                menuItemNames = new String[size];
                menuItemsLength = size;

                // menuItemsLinks = new int[size]; // probly won't need this
                int index = 0;
                for (int i = size1; i <= size2; i++)
                {
                    menuItemNames[index] = (String)i;
                    index++;
                }
            }
            else
            {
                error("range invalid");
            }
        }
    }
    else
    {
        error("name too long");
    }
}