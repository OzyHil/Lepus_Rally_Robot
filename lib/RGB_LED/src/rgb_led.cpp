#include "rgb_led.h"

RgbLed::RgbLed(uint8_t r_pin, uint8_t g_pin, uint8_t b_pin)
    : _r_pin(r_pin), _g_pin(g_pin), _b_pin(b_pin), _color{RgbColors::OFF} {}

void RgbLed::begin() {
    pinMode(_r_pin, OUTPUT);
    pinMode(_g_pin, OUTPUT);
    pinMode(_b_pin, OUTPUT);
    off();
}

void RgbLed::set_color(RgbColor color) {
    _color = color;
}

void RgbLed::apply(bool state) {
    analogWrite(_r_pin, state ? _color.r : 0);
    analogWrite(_g_pin, state ? _color.g : 0);
    analogWrite(_b_pin, state ? _color.b : 0);
}

void RgbLed::apply_pwm(uint8_t duty) {
    analogWrite(_r_pin, (_color.r * duty) / 255);
    analogWrite(_g_pin, (_color.g * duty) / 255);
    analogWrite(_b_pin, (_color.b * duty) / 255);
}