#pragma once
#include "led_controller.h"

struct RgbColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

namespace RgbColors {
    const RgbColor RED     = {255, 0,   0};
    const RgbColor GREEN   = {0,   255, 0};
    const RgbColor BLUE    = {0,   0,   255};
    const RgbColor YELLOW  = {255, 255, 0};
    const RgbColor PURPLE  = {128, 0,   128};
    const RgbColor WHITE   = {255, 255, 255};
    const RgbColor OFF     = {0,   0,   0};
}

class RgbLed : public LedController {
public:
    RgbLed(uint8_t r_pin, uint8_t g_pin, uint8_t b_pin);

    void begin();
    void set_color(RgbColor color);

protected:
    void apply(bool state) override;
    void apply_pwm(uint8_t duty) override;

private:
    uint8_t _r_pin;
    uint8_t _g_pin;
    uint8_t _b_pin;

    RgbColor _color;
};