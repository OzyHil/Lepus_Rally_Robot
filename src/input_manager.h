#pragma once

#include <Arduino.h>
#include "KY032.h"
#include "button.h"

enum class InputEvent {
    NONE,
    READY_BUTTON,
    RESET_BUTTON,
    BUTTON_LONG_PRESS,
    OBSTACLE_TRIGGERED,
    DISTANCE_APPROACHING,
    DISTANCE_REACHED
};

class InputManager {
public:
    explicit InputManager(
        uint8_t obstacle_sensor_pin,
        uint8_t button_pin
    );
    
    void begin();
    void update();
    InputEvent get_event();
    void clear_events();

private:
    InputEvent _event;   
    InputEvent _last_event;
    KY032 _obstacle_sensor;
    Button _button;
    void handleButtonEvent(InputEvent ev);
};