#include "Menu.h"

void Menu::setMenuStructure(int menuId)
{
    String name;
    String *tmp1;
    int *tmp2;
    int size1;
    int size2;

    delete[] menuItemNames;
    delete[] menuItemsLinks;

    switch (menuId)
    {
    case 1:
    {
        name = "Main menu";
        static String tmp01[] = {
            "test1",
            "test2",
            "test3",
            "test4",
            "test5"};
        static int tmp02[] = {1, 2, 3, 4, 5};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

        break;
    }
    case 2:
    {
        name = "Second menu";
        static String tmp01[] = {
            "randmom1",
            "short2",
            "veeery long3",
            "ha4",
            "yo5",
            "hello kelo to6"};
        static int tmp02[] = {1, 6515641, 3, 4, 5, 6};

        tmp1 = tmp01;
        tmp2 = tmp02;
        size1 = sizeof(tmp01) / sizeof(tmp01[0]);
        size2 = sizeof(tmp02) / sizeof(tmp02[0]);

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

    for (int i = 0; i < size1; i++)
    {
        if (tmp1[i].length() > cols - 2)
        {
            error("menu it. t.long");
        }
    }

    if (name.length() <= cols)
    {

        if (size1 == size2)
        {
            int size = size1;
            menuItemNames = new String[size];
            menuItemsLinks = new int[size];
            menuItemsLength = size;

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