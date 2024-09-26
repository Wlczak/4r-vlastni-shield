#include "RGB.h"

RGB::RGB(int rgb_pixels, int rgb_pin)
    : neofruit(rgb_pixels, rgb_pin, NEO_GRB + NEO_KHZ800) // Initialize NeoPixel object
{
    pixels = rgb_pixels;
    neofruit.begin();            // Initialize the NeoPixel strip
    neofruit.setBrightness(1); // Optional: Set brightness (0-255)
}

void RGB::light()
{
    for (int i = 0; i < pixels; i++)
    {
        neofruit.setPixelColor(i, neofruit.Color(255, 255, 255));
        neofruit.show();
    }
}