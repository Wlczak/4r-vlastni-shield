#include "Menu.h"

void Menu::setMenuStructure(int menuId)
{
    String name;
    int type;
    String *tmp1;
    int *tmp2;
    int size1;
    int size2;
    int incrementBy = -1;
    int settingIndex = -1;
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
            "Neopixel", "Debug LEDs", "Cursor"};
        static int tmp02[] = {6, 44, 43};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;
    }
    case 43:
    {
        name = "Cursor";
        type = S_SETTINGS; // select menu
        isRange = false;
        settingIndex = SET_SHOW_CURSOR;

        static String tmp01[] = {
            "on", "off"};

        tmp1 = tmp01;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);

        break;
    }
    case 44:
    {
        name = "Debug LEDs";
        type = S_SETTINGS; // select menu
        isRange = false;
        settingIndex = SET_DEBUG_LED;

        static String tmp01[] = {
            "off", "blue", "red", "both"};

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
            "Length test",
            "Range test",
            "Trigger errors",
            "Short2",
            "Veeery long3",
            "Ha4",
            "Yo5",
            "Hello kelo to6"};
        static int tmp02[] = {1, 51, 52, 53, 6515641, 34, 420, 59, 17};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;
    }

    case 51:
    {
        name = "Length test";
        type = S_SETTINGS; // select menu
        isRange = false;
        settingIndex = 2;

        static String tmp01[] = {
            "1", "12", "123", "1234", "12345", "123456", "1234567", "12345678", "123456789", "1234567891", "12345678912", "123456789123", "1234567891234", "12345678912345"};

        tmp1 = tmp01;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);

        break;
    }

    case 52:
        name = "Range";
        type = S_SETTINGS; // select menu
        isRange = true;
        settingIndex = 1;

        // range size
        size1 = 0;
        size2 = 10000;

        break;

    case 53:
    {
        name = "Break stuff";
        type = S_NAVIGATION_MENU;
        static String tmp01[] = {
            "Main menu",
            "Length test12132212323123231132 this is too long on purpose :-)",
            "Range test"};
        static int tmp02[] = {1, 51, 52, 6515641, 34, 420, 59, 17};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;
    }
    case 6:
    {
        name = "Neopixel";
        type = S_NAVIGATION_MENU;
        static String tmp01[] = {
            "Effects",
            "Brightness"};
        static int tmp02[] = {61, 62};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;
    }
    case 61:
    {
        name = "Effects";
        type = S_SETTINGS; // select menu
        isRange = false;
        settingIndex = SET_NEOPIXEL_EFFECT;

        static String tmp01[] = {
            "blank", "white"};

        tmp1 = tmp01;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);

        break;
    }
    case 62:
        name = "Brightness";
        type = S_SETTINGS; // select menu
        isRange = true;
        settingIndex = SET_NEOPIXEL_BRIGHTNESS;

        // range size
        size1 = 0;
        size2 = 255;
        incrementBy = 10;

        break;
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
            menuIncrement = -1;
            if (settingIndex < 0)
            {
                error("set index !set");
            }
            else if (settingIndex > settingSlots)
            {
                error("invalid set id");
            }
            else
            {
                currentSettingIndex = settingIndex;
            }
            if (isRange)
            {
                if (size1 < size2)
                {
                    if (incrementBy <= 0)
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
                        int size = size2 - size1 + 1;
                        menuItemsLength = (int)floor(size / incrementBy) + 2;

                        menuFirstValue = size1;
                        menuLastValue = size2;
                        menuIncrement = incrementBy;

                        menuItemNames = new String[menuItemsLength];
                        menuItemsLinks = new int[menuItemsLength];

                        int index = 0;

                        for (int i = size1; i < size2; i += incrementBy)
                        {
                            menuItemNames[index] = (String)(size1 + (index * incrementBy));
                            Serial.println((String)(size1 + (index * incrementBy)));

                            index++;
                        }
                        menuItemNames[index] = (String)size2;
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