#ifndef RGB_H
#define RGB_H

#include <Adafruit_NeoPixel.h>

#include <Arduino.h>

class RGB {
public:
    RGB(int rgb_pixels, int rgb_pin);
    void rainbow(uint8_t wait);

private:
    Adafruit_NeoPixel neofruit;
    uint32_t Wheel(byte WheelPos);
};

#endif
