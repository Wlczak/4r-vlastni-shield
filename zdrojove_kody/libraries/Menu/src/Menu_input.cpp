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
    float temp;
    switch (deviceId)
    {
    case 1:

        sensors.setWaitForConversion(false);
        sensors.requestTemperatures();
        temp = sensors.getTempCByIndex(0);
        if (temp != DEVICE_DISCONNECTED_C)
        {
            output = (String)temp;
            output += (char)0b10100000;
            output += (char)223;
            output += "C";
        }
        else
        {
            output = "DISCONNECTED";
        }

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
