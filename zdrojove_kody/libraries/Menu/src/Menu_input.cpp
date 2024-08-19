#include "Menu.h"

void Menu::inputUp()
{
    inputBuffer = 1;
}
void Menu::inputDown()
{
    inputBuffer = 2;
}
void Menu::inputEnter()
{
    inputBuffer = 3;
}
void Menu::inputBack()
{
    inputBuffer = 4;
}
String Menu::readDeviceInput(int deviceId)
{
    String output = "";
    switch (deviceId)
    {
    case 1:;
        output = (String) random(13, 69);
        output += (char) 0b10100000;
        output += (char) 223;
        output += "C";
        break;

    default:
        output = "NaN";
    }
    return output;
}
