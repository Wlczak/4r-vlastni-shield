#include "Menu.h"
#include <cstdint>
#include <iostream>
#include <bitset>
#include "LCDChars.h"

typedef uint8_t byte;

int test;
Menu::Menu()
{
    test = 15;
}
int main(){
    Menu menu;
    std::cout << test;
    return 0;
}