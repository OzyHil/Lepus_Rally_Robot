#pragma once
#include <Arduino.h>

class KY032 {
public:
    KY032(uint8_t data_pin,
          int8_t enable_pin = -1);

    void begin();

    bool triggered();
    void reset();

    void enable();
    void disable();

private:
    uint8_t  _data_pin;
    int8_t   _enable_pin;   
    uint32_t _debounce_ms;

    bool     _last_state;
    uint32_t _last_change_time;
    bool     _triggered;

    static constexpr uint32_t DEBOUNCE_MS = 10;

    bool has_enable() const;
};
