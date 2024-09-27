#ifndef RGB_H
#define RGB_H

#include <Adafruit_NeoPixel.h>

#include <Arduino.h>

class RGB
{
public:
    RGB(int rgb_pixels, int rgb_pin);
    // renders
    void render(int effectId, int brightness);

    void blank();
    void light();

    enum class Types : int
    {
        Blank = 0,
        Rainbow = 1
    };

private:
    int pixels;
    Adafruit_NeoPixel neofruit;
};

#endif
