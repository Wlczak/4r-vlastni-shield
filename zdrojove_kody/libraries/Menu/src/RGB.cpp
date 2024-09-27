#include "RGB.h"

#define EFFECT_BLANK 0
#define EFFECT_RAINBOW 1

RGB::RGB(int rgb_pixels, int rgb_pin)
    : neofruit(rgb_pixels, rgb_pin, NEO_GRB + NEO_KHZ800) // Initialize NeoPixel object
{
    pixels = rgb_pixels;
    neofruit.begin(); // Initialize the NeoPixel strip
}

void RGB::render(int effectId, int brightness)
{
    neofruit.setBrightness(brightness);
    switch (effectId)
    {
    case EFFECT_BLANK:
        blank();
        break;
    case EFFECT_RAINBOW:
        light();
        break;
    default:
        break;
    }
}

void RGB::blank(){
    for (int i = 0; i < pixels; i++)
    {
        neofruit.setPixelColor(i, neofruit.Color(0, 0, 0));
        neofruit.show();
    }
}

void RGB::light()
{
    for (int i = 0; i < pixels; i++)
    {
        neofruit.setPixelColor(i, neofruit.Color(255, 255, 255));
        neofruit.show();
    }
}