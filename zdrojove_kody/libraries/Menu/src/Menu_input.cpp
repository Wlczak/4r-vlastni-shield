#include "Menu.h"

void Menu::inputUp()
{
    inputBuffer = IN_UP;
}
void Menu::inputDown()
{
    inputBuffer = IN_DOWN;
}
void Menu::inputEnter()
{
    inputBuffer = IN_ENTER;
}
void Menu::inputBack()
{
    inputBuffer = IN_BACK;
}
String Menu::readDeviceInput(int deviceId)
{
    String output = "";
    String test = "1";
    switch (deviceId)
    {
    case 1:
        sensors.setWaitForConversion(false);
        sensors.requestTemperatures();
        output = (String)sensors.getTempCByIndex(0);
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
        output = (String)analogRead(A0);
        break;

    default:
        output = "inval dev id";
    }
    return output;
}
