#include "ky032.h"

KY032::KY032(
    uint8_t _data_pin,
    int8_t enable_pin)

    : _data_pin(_data_pin),
      _enable_pin(enable_pin),
      _last_state (digitalRead(_data_pin)),
      _last_change_time(0),
      _triggered(false) {}

void KY032::begin() {
    pinMode(_data_pin, INPUT);

    if (has_enable()) {
        pinMode(_enable_pin, OUTPUT);
        digitalWrite(_enable_pin, HIGH);
    }
}

bool KY032::triggered() {
    bool current_state = (digitalRead(_data_pin) == HIGH);
    uint32_t now = millis();

    if (current_state != _last_state) {
        _last_state = current_state;
        _last_change_time = now;
    }

    if (current_state &&
        (now - _last_change_time >= DEBOUNCE_MS) &&
        !_triggered) {

        _triggered = true;
        return true;
    }

    return false;
}

void KY032::reset() {
    _triggered = false;
}

void KY032::enable() {
    if (has_enable()) {
        digitalWrite(_enable_pin, HIGH);
    }
}

void KY032::disable() {
    if (has_enable()) {
        digitalWrite(_enable_pin, LOW);
    }
}

bool KY032::has_enable() const {
    return _enable_pin >= 0;
}