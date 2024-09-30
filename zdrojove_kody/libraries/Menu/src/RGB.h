#ifndef RGB_H
#define RGB_H

#include <Adafruit_NeoPixel.h>

#include <Arduino.h> // imports arduino stadard lib

class RGB
{
public:
    RGB(int rgb_pixels, int rgb_pin);
    // renders rgb strip effects
    void render(int effectId, int brightness);

    // effects methods
    void blank();
    void light();

private:
    Adafruit_NeoPixel neofruit;
    int pixels;
};

#endif
