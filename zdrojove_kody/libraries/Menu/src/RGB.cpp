#include "RGB.h"

RGB::RGB(int rgb_pixels, int rgb_pin)
    : neofruit(rgb_pixels, rgb_pin, NEO_GRB + NEO_KHZ800) // Initialize NeoPixel object
{
    neofruit.begin();           // Initialize the NeoPixel strip
    neofruit.setBrightness(100); // Optional: Set brightness (0-255)
}

void RGB::rainbow(uint8_t wait)
{
    // Cycle through a rainbow
    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
    {
        for (int i = 0; i < neofruit.numPixels(); i++)
        {
            int pixelHue = firstPixelHue + (i * 65536L / neofruit.numPixels());
            neofruit.setPixelColor(i, neofruit.gamma32(neofruit.ColorHSV(pixelHue)));
        }
        neofruit.show();
        delay(wait);
    }
}

// Helper function to generate rainbow colors across 0-255 positions.
uint32_t RGB::Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return neofruit.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return neofruit.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return neofruit.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}