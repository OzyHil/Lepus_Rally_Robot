#include "led_controller.h"

void LedController::on() {
    _mode = LedMode::ON;
    _state = true;
    apply(true);
}

void LedController::off() {
    _mode = LedMode::OFF;
    _state = false;
    apply(false);
}

void LedController::blink(uint32_t interval_ms) {
    _mode = LedMode::BLINK;
    _interval_ms = interval_ms;
    _last_toggle = millis();
}

void LedController::pwm(uint8_t duty) {
    _mode = LedMode::PWM;
    _pwm_duty = duty;
    apply_pwm(duty);
}

void LedController::update() {
    if (_mode != LedMode::BLINK) return;

    uint32_t now = millis();
    if (now - _last_toggle >= _interval_ms) {
        _last_toggle = now;
        _state = !_state;

        if (_pwm_duty > 0) {
            apply_pwm(_state ? _pwm_duty : 0);
        } else {
            apply(_state);
        }
    }
}