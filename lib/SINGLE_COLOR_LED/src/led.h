#pragma once
#include "led_controller.h"

class Led : public LedController {
public:
    explicit Led(uint8_t pin);
    void begin() override;

protected:
    void apply(bool state) override;
    void apply_pwm(uint8_t duty) override;

private:
    uint8_t _pin;
};
