#ifndef SOLID2EFFECT_H
#define SOLID2EFFECT_H

#include "NeoPixelEffect.h"

class Solid2Effect : public NeoPixelEffect {
public:

    virtual void init(NeoPixelStrip *strip, uint8_t numParams, uint8_t params[])
    {
        color0r_ = params[0];
        color0g_ = params[1];
        color0b_ = params[2];

        color1r_ = params[3];
        color1g_ = params[4];
        color1b_ = params[5];

        delay_ = params[6];

        index_ = 0;
    }

    virtual void step(NeoPixelStrip *strip)
    {
        for (size_t i = 0; i < strip->numPixels(); ++i) {
            if ((i % 2) == 0) {
                if (index_ == 0) {
                    strip->setPixelColor(i, color0r_, color0g_, color0b_);
                } else {
                    strip->setPixelColor(i, color1r_, color1g_, color1b_);
                }
            } else {
                if (index_ == 0) {
                    strip->setPixelColor(i, color1r_, color1g_, color1b_);
                } else {
                    strip->setPixelColor(i, color0r_, color0g_, color0b_);
                }
            }
        }
        strip->show();

        if (delay_ > 0) {
            index_ = index_ + 1;
            index_ = (index_ & 2);
            strip->delay(delay_);
        }
    }

private:

    uint8_t color0r_;
    uint8_t color0g_;
    uint8_t color0b_;

    uint8_t color1r_;
    uint8_t color1g_;
    uint8_t color1b_;


    uint8_t delay_;

    int index_;

};

#endif
