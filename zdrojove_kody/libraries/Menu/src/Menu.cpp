#include "Menu.h"
#include "LCDChars.h"

LCDChars lcdChars;
Menu::Menu()
{
    LCDChars lcdChars;
}
void Menu::loadChars()
{
    //lcdChars.begin();
    lcdChars.loadChars();
};