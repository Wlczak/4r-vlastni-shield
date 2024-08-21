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
    String test = "1";
    switch (deviceId)
    {
    case 1:
        output = (String)(random(1, 20));
        output += (char)0b10100000;
        output += (char)223;
        output += "C";
        break;
    case 3:
        output = (String)(random(1, 20));
        output += (char)0b10100000;
        output += "(char)223;";
        break;

    case 2:
        output = test.length();
        break;

    default:
        output = "inval dev id";
    }
    return output;
}
