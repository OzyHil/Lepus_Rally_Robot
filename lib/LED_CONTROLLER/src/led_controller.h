#pragma once
#include <Arduino.h>

enum class LedMode {
    OFF,
    ON,
    BLINK,
    PWM
};

class LedController {
public:
    virtual void begin() = 0;
    virtual void update();

    void on();
    void off();
    void blink(uint32_t interval_ms);
    void pwm(uint8_t duty);

protected:
    virtual void apply(bool state) = 0;
    virtual void apply_pwm(uint8_t duty) = 0;

    LedMode _mode = LedMode::OFF;

    uint32_t _interval_ms = 0;
    uint32_t _last_toggle = 0;
    bool _state = false;

    uint8_t _pwm_duty = 0;
};