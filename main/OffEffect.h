#ifndef OFFEFFECT_H
#define OFFEFFECT_H

#include "NeoPixelEffect.h"

class OffEffect : public NeoPixelEffect {
public:

    virtual void init(NeoPixelStrip *strip, uint8_t numParams, uint8_t params[])
    {
        strip->clear();
        strip->show();
    }

    virtual void step(int pin)
    {}

};

#endif
