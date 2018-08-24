#include "EffectManager.h"
#include "OffEffect.h"
#include "SolidEffect.h"
#include "Solid2Effect.h"
#include "Solid3Effect.h"
#include "CylonEffect.h"
#include "PulseEffect.h"

EffectManager::EffectManager(int pin) : pin_(pin), pixels_(0), effectNum_(-1), effect_(0), strip_(0)
{}

EffectManager::~EffectManager()
{
    if (strip_) {
        delete strip_;
    }
}

void EffectManager::setNumPixels(int pixels)
{
    if (pixels != pixels_) {
        if (strip_) {
            delete strip_;
        }
        pixels_ = pixels;

        strip_ = new NeoPixelStrip(pixels_, pin_);
        strip_->begin();
    }
}

void EffectManager::setEffect(const uint8_t effectNum, uint8_t numParams, uint8_t params[])
{
    if (effectNum != effectNum_) {
        if (effect_) {
            strip_->clear();
            delete effect_;
            effect_ = 0;
        }

        if (effectNum == EFFECT_OFF) {
            effect_ = new OffEffect();

        } else if (effectNum == EFFECT_SOLID) {
            effect_ = new SolidEffect();

        } else if (effectNum == EFFECT_SOLID2) {
            effect_ = new Solid2Effect();

        } else if (effectNum == EFFECT_SOLID3) {
            effect_ = new Solid3Effect();

        } else if (effectNum == EFFECT_CYLON) {
            effect_ = new CylonEffect();

        } else if (effectNum == EFFECT_PULSE) {
            effect_ = new PulseEffect();

        }

        if (effect_) {
            effect_->init(strip_, numParams, params);
        }
    }
}

void EffectManager::step()
{
    if (effect_) {
        effect_->step(strip_);
    }
}
