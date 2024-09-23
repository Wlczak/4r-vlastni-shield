#ifndef RGB_H
#define RGB_H

#include <Adafruit_NeoPixel.h>

#include <Arduino.h>

class RGB {
public:
    RGB(int rgb_pixels, int rgb_pin);
    void light();

private:
    Adafruit_NeoPixel neofruit;
};

#endif
