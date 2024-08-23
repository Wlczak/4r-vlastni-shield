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

    programType = S_DEFAULT;
    if (menuItemNames != nullptr)
    {
        delete[] menuItemNames;
        menuItemNames = nullptr;
    }
    if (menuItemsLinks != nullptr)
    {
        delete[] menuItemsLinks;
        menuItemsLinks = nullptr;
    }

    switch (menuId)
    {
    case 1:
    {
        name = "Main menu";
        type = S_NAVIGATION_MENU;
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
        type = S_SENSOR_READOUT;
        deviceId = 1;
        break;
    }
    case 3:
    {
        name = "photo";
        type = S_SENSOR_READOUT;
        deviceId = 2;
        break;
    }
    case 4:
    {
        name = "Settings";
        type = S_NAVIGATION_MENU;
        static String tmp01[] = {
            "Cursor", "range test", "lenght test"};
        static int tmp02[] = {43, 42, 41};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;
    }

    case 41:
    {
        name = "Length test";
        type = S_SETTINGS; // select menu
        isRange = false;

        static String tmp01[] = {
            "1", "12", "123", "1234", "12345", "123456", "1234567", "12345678", "123456789", "1234567891", "12345678912", "123456789123", "1234567891234", "12345678912345"};

        tmp1 = tmp01;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);

        break;
    }
    case 42:
        name = "Range";
        type = S_SETTINGS; // select menu
        isRange = true;

        // range size
        size1 = 0;
        size2 = 10;

        break;
    case 43:
    {
        name = "Cursor";
        type = S_SETTINGS; // select menu
        isRange = false;

        static String tmp01[] = {
            "on", "off"};

        tmp1 = tmp01;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);

        break;
    }
    case 5:
    {
        name = "Debug menu";
        type = S_NAVIGATION_MENU;
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
        type = S_NAVIGATION_MENU;
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

        if (type != S_SETTINGS) // reset currentSettingsIndex if not in context of settings menu
        {
            currentSettingIndex = -1;
        }

        switch (type)
        {
        case S_NAVIGATION_MENU:
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
            break;
        case S_SETTINGS:
            if (isRange)
            {
                if (size1 < size2)
                {
                    int size = size2 - size1 + 1;
                    menuItemNames = new String[size];
                    menuItemsLength = size;

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
            else
            {
                for (int i = 0; i < size1; i++)
                {
                    if (tmp1[i].length() > cols - 2)
                    {
                        error("menu" + (String)i + "it. t.long");
                    }
                }

                menuItemNames = new String[size1];
                menuItemsLength = size1;

                for (int i = 0; i < size1; i++)
                {
                    menuItemNames[i] = tmp1[i];
                }
            }
            break;
        }
    }
    else
    {
        error("name too long");
    }
}