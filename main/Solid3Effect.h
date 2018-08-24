#ifndef SOLID3EFFECT_H
#define SOLID3EFFECT_H

#include "NeoPixelEffect.h"

class Solid3Effect : public NeoPixelEffect {
public:

    virtual void init(NeoPixelStrip *strip, uint8_t numParams, uint8_t params[])
    {
        r0 = params[0]; g0 = params[1]; b0 = params[2];
        r1 = params[3]; g1 = params[4]; b1 = params[5];
        r2 = params[6]; g2 = params[7]; b2 = params[8];
        delay_ = params[9];
        index_ = 0;
    }

    virtual void step(NeoPixelStrip *strip)
    {
        for (size_t i = 0; i < strip->numPixels(); ++i) {
            if ((i % 3) == 0) {
                switch (index_) {
                case 0:
                    strip->setPixelColor(i, r0, g0, b0);
                    break;
                case 1:
                    strip->setPixelColor(i, r1, g1, b1);
                    break;
                default:
                    strip->setPixelColor(i, r2, g2, b2);
                }
            } else if ((i % 3) == 1) {

                switch (index_) {
                case 0:
                    strip->setPixelColor(i, r1, g1, b1);
                    break;
                case 1:
                    strip->setPixelColor(i, r2, g2, b2);
                    break;
                default:
                    strip->setPixelColor(i, r0, g0, b0);
                    break;
                }

            } else {
                switch (index_) {
                case 0:
                    strip->setPixelColor(i, r2, g2, b2);
                    break;
                case 1:
                    strip->setPixelColor(i, r0, g0, b0);
                    break;
                default:
                    strip->setPixelColor(i, r1, g1, b1);
                    break;
                }
            }
        }
        strip->show();

        if (delay_ > 0) {
            index_ = index_ + 1;
            index_ = (index_ % 3);
            strip->delay(delay_);
        }
    }


private:

    uint8_t r0, g0, b0;
    uint8_t r1, g1, b1;
    uint8_t r2, g2, b2;
    uint8_t delay_;

    int index_;
};

#endif
