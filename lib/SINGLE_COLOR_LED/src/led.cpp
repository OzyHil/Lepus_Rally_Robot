#include "led.h"

Led::Led(uint8_t pin) : _pin(pin) {}

void Led::begin() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void Led::apply(bool state) {
    analogWrite(_pin, 0);               
    digitalWrite(_pin, state ? HIGH : LOW);
}

void Led::apply_pwm(uint8_t duty) {
    analogWrite(_pin, duty);
}