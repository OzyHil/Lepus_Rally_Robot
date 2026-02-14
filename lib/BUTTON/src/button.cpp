#include "button.h"

Button::Button(uint8_t pin) : _pin(pin) {}

void Button::begin() {
    pinMode(_pin, INPUT_PULLUP);
}

void Button::update() {
    _event = ButtonEvent::NONE;

    bool current = !digitalRead(_pin);
    uint32_t now = millis();

    if (current && !_last_state) {
        if (now - _last_press_time > DEBOUNCE_MS) {
            _click_count++;
            _last_press_time = now;
        }
    }

    if (current && (now - _last_press_time > LONG_PRESS_MS)) {
        _event = ButtonEvent::LONG_PRESS;
        _click_count = 0;
    }

    if (!current && _click_count > 0 && (now - _last_press_time > DOUBLE_CLICK_MS)) {
        if (_click_count == 1) 
            _event = ButtonEvent::SINGLE_CLICK;
        else 
            _event = ButtonEvent::DOUBLE_CLICK;

        _click_count = 0;
    }
    _last_state = current;
}

ButtonEvent Button::get_event() {
    return _event;
}

void Button::clear_event() {
    _event = ButtonEvent::NONE;
}
