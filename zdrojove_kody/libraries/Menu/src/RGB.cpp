#include "RGB.h"

RGB::RGB(int rgb_pixels, int rgb_pin)
    : neofruit(rgb_pixels, rgb_pin, NEO_GRB + NEO_KHZ800) // Initialize NeoPixel object
{
    neofruit.begin();           // Initialize the NeoPixel strip
    neofruit.setBrightness(50); // Optional: Set brightness (0-255)
}

void RGB::light()
{
    // Light up all pixels in red
    for (int i = 0; i < neofruit.numPixels(); i++)
    {
        neofruit.setPixelColor(i, neofruit.Color(255, 0, 0)); // Red
    }
    neofruit.show(); // Update the strip to show the color
}
