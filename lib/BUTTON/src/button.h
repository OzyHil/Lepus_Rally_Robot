#pragma once
#include <Arduino.h>

enum class ButtonEvent {
    NONE,
    SINGLE_CLICK,
    DOUBLE_CLICK,
    LONG_PRESS
};

class Button {
public:
    explicit Button(uint8_t pin);
    void begin();
    void update();
    ButtonEvent get_event();
    void clear_event();

private:
    uint8_t _pin;
    bool _last_state = false;
    uint32_t _last_press_time = 0;
    uint8_t _click_count = 0;

    ButtonEvent _event = ButtonEvent::NONE;

    static constexpr uint32_t DEBOUNCE_MS = 250;
    static constexpr uint32_t DOUBLE_CLICK_MS = 1000;
    static constexpr uint32_t LONG_PRESS_MS = 3000;
};