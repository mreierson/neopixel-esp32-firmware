#ifndef PULSEEFFECT_H
#define PULSEEFFECT_H

#include "NeoPixelEffect.h"

class PulseEffect : public NeoPixelEffect {
public:

    virtual void init(NeoPixelStrip *strip, uint8_t numParams, uint8_t params[])
    {
        red1_ = params[0];
        green1_ = params[1];
        blue1_ = params[2];
        red2_ = params[3];
        green2_ = params[4];
        blue2_ = params[5];

        delay_ = params[7];

        t_ = 0;
        step_ = params[6] / 255.0;
    }

    virtual void step(NeoPixelStrip *strip)
    {
        t_ = t_ + step_;
        if (t_ >= 1.0) {
            step_ *= -1.0;
        } else if (t_ <= 0) {
            step_ *= -1.0;
        }

        uint8_t red, green, blue;

        lerpRGB(red1_, green1_, blue1_, red2_, green2_, blue2_, t_, red, green, blue);

        for (int i = 0; i < strip->numPixels(); ++i) {
            strip->setPixelColor(i, red, green, blue);
        }

        strip->show();
        if (delay_ > 0) {
            strip->delay(delay_);
        }
    }

private:

    uint8_t red1_;
    uint8_t green1_;
    uint8_t blue1_;
    uint8_t red2_;
    uint8_t green2_;
    uint8_t blue2_;
    uint8_t delay_;

    float t_;
    float step_;

};

#endif
