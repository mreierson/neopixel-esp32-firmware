#ifndef NEOPIXELEFFECT_H
#define NEOPIXELEFFECT_H

#include "NeoPixelStrip.h"

class NeoPixelEffect {
public:

    virtual ~NeoPixelEffect()
    {}

    virtual void init(NeoPixelStrip *strip, uint8_t numParams, uint8_t params[])
    {}

    virtual void step(NeoPixelStrip *strip)
    {}

protected:

    void lerpRGB(uint8_t red1, uint8_t green1, uint8_t blue1, uint8_t red2, uint8_t green2, uint8_t blue2, float t, uint8_t &red, uint8_t &green, uint8_t &blue)
    {
        red = red1 + (red2 - red1) * t;
        green = green1 + (green2 - green1) * t;
        blue = blue1 + (blue2 - blue1) * t;
    }
};

#endif
