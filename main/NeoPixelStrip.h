#ifndef NEOPIXELSTRIP_H
#define NEOPIXELSTRIP_H

#include "freertos/FreeRTOS.h"

extern "C" {
#include "ws2812.h"
}


class NeoPixelStrip {
public:

    NeoPixelStrip(uint32_t numPixels, int pin);
    virtual ~NeoPixelStrip();

    virtual void begin();
    virtual void clear();
    virtual void show();

    virtual void delay(uint32_t millis);

    virtual size_t numPixels();

    // virtual void setPixelColor(uint32_t pixelNum, uint32_t color);
    virtual void setPixelColor(uint32_t pixelNum, uint8_t r, uint8_t g, uint8_t b);

    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

private:

    uint32_t numPixels_;
    uint8_t *pixels_;
    int pin_;

};

#endif
