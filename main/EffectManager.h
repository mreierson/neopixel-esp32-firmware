#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H

#include "NeoPixelEffect.h"
#include "NeoPixelStrip.h"

class EffectManager {
public:

    const uint8_t EFFECT_OFF = 0x0;
    const uint8_t EFFECT_SOLID = 0x01;
    const uint8_t EFFECT_SOLID2 = 0x02;
    const uint8_t EFFECT_SOLID3 = 0x03;
    const uint8_t EFFECT_CYLON = 0x04;
    const uint8_t EFFECT_PULSE = 0x05;

    EffectManager(int pin);
    virtual ~EffectManager();

    void setNumPixels(int pixels);
    void setEffect(const uint8_t effectNum, uint8_t numParams, uint8_t params[]);

    void step();

private:

    int pin_;
    int pixels_;
    int effectNum_;
    NeoPixelEffect *effect_;
    NeoPixelStrip *strip_;

};

#endif
