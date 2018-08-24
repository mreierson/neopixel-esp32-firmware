#ifndef CYLONEFFECT_H
#define CYLONEFFECT_H

#include "NeoPixelEffect.h"

class CylonEffect : public NeoPixelEffect {
public:

    virtual void init(NeoPixelStrip *strip, uint8_t numParams, uint8_t params[])
    {
        red_ = params[0];
        green_ = params[1];
        blue_ = params[2];
        length_ = params[3];
        delay_ = params[4];

        curr_ = -1;
        dir_ = 1;
    }

    virtual void step(NeoPixelStrip *strip)
    {
        int numPixels = strip->numPixels();

        curr_ += dir_;

        if (dir_ > 0) {
            for (int i = curr_; i >= 0 && (dir_ > 0); i--) {
                if (i < numPixels) {
                    int currColor = 255 - ((curr_ - i) * (255.0 / length_));
                    if (currColor < 0) {
                        currColor = 0;
                    }
                    if ((currColor == 0) && (i == numPixels - 1)) {
                        curr_ = numPixels;
                        dir_ = -1;
                    } else {
                        uint8_t red = red_ * (currColor / 255.0f);
                        uint8_t green = green_ * (currColor / 255.0f);
                        uint8_t blue = blue_ * (currColor / 255.0f);
                        strip->setPixelColor(i, red, green, blue);
                    }
                }
            }
        } else {
            for (int i = curr_; i < numPixels && (dir_ < 0); i++) {
                if (i >= 0) {
                    int currColor = 255 - ((i - curr_) * (255.0 / length_));
                    if (currColor < 0) {
                        currColor = 0;
                    }
                    if ((currColor == 0) && (i == 0)) {
                        curr_ = -1;
                        dir_ = 1;
                    } else {
                        uint8_t red = red_ * (currColor / 255.0f);
                        uint8_t green = green_ * (currColor / 255.0f);
                        uint8_t blue = blue_ * (currColor / 255.0f);
                        strip->setPixelColor(i, red, green, blue);
                    }
                }
            }
        }

        strip->show();

    }

private:

    uint8_t red_;
    uint8_t green_;
    uint8_t blue_;
    uint8_t length_;
    uint8_t delay_;

    int dir_;
    int max_;
    int curr_;

};


#endif
