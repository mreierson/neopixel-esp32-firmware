#include "NeoPixelStrip.h"
#include "esp_event.h"
#include <string.h>

NeoPixelStrip::NeoPixelStrip(uint32_t numPixels, int pin) : numPixels_(numPixels), pin_(pin)
{
    pixels_ = new uint8_t[numPixels * 3];
}

NeoPixelStrip::~NeoPixelStrip()
{
    if (pixels_) {
        delete [] pixels_;
    }
}

void NeoPixelStrip::begin()
{
    ws2812_init(pin_, numPixels_);
}

void NeoPixelStrip::clear()
{
    memset(pixels_, 0, numPixels_ * 3);
}

void NeoPixelStrip::show()
{
    ws2812_setColors(numPixels_, pixels_);
}

size_t NeoPixelStrip::numPixels()
{
    return numPixels_;
}

/*
void NeoPixelStrip::setPixelColor(uint32_t pixelNum, uint32_t color)
{
    pixels_[pixelNum].num = color;
}
*/

void NeoPixelStrip::setPixelColor(uint32_t pixelNum, uint8_t r, uint8_t g, uint8_t b)
{
    pixels_[pixelNum * 3 + 0] = g;
    pixels_[pixelNum * 3 + 1] = r;
    pixels_[pixelNum * 3 + 2] = b;
}

void NeoPixelStrip::delay(uint32_t millis)
{
    if (millis > 0) {
        vTaskDelay(millis / portTICK_PERIOD_MS);
    }
    // vTaskDelay(millis / portTICK_PERIOD_MS);
}

uint32_t NeoPixelStrip::Color(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t) r << 16) | ((uint32_t) g << 8) | b;
}

uint32_t NeoPixelStrip::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    return ((uint32_t) w << 24) | ((uint32_t) r << 16) | ((uint32_t) g << 8) | b;
}
