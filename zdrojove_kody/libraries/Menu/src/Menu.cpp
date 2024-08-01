#include "Menu.h"

Menu::Menu()
{
    LCDChars lcdChars;
}
void Menu::loadChars()
{
    lcdChars.loadChars();
};

void Menu::debug()
{
    lcdChars.writeAllChars();
};