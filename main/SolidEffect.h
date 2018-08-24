#ifndef SOLIDEFFECT_H
#define SOLIDEFFECT_H

#include "NeoPixelEffect.h"

class SolidEffect : public NeoPixelEffect {
public:

    virtual void init(NeoPixelStrip *strip, uint8_t numParams, uint8_t params[])
    {
        for (size_t i = 0; i < strip->numPixels(); ++i) {
            strip->setPixelColor(i, params[0], params[1], params[2]);
        }
        strip->show();
    }

    virtual void step(NeoPixelStrip *strip)
    {}

};

#endif
