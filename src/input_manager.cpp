#include "input_manager.h"

InputManager::InputManager(uint8_t obstacle_sensor_pin, uint8_t button_pin)
    : _obstacle_sensor(obstacle_sensor_pin),
      _button(button_pin),
      _event(InputEvent::NONE)
{
}

void InputManager::begin() {
    _obstacle_sensor.begin();
    _button.begin();
}

void InputManager::update() {
    _button.update();
   
    if (_obstacle_sensor.triggered() && _last_event == InputEvent::READY_BUTTON) {
        _event = InputEvent::OBSTACLE_TRIGGERED;
        _last_event = _event;
        return;
    }

    switch (_button.get_event()) {   
        case ButtonEvent::SINGLE_CLICK:
            _obstacle_sensor.reset();
            handleButtonEvent(InputEvent::READY_BUTTON);
            break;
        case ButtonEvent::DOUBLE_CLICK: handleButtonEvent(InputEvent::RESET_BUTTON); break;
        case ButtonEvent::LONG_PRESS: handleButtonEvent(InputEvent::BUTTON_LONG_PRESS); break;
    }
}

InputEvent InputManager::get_event() {
    return _event;
}

void InputManager::clear_events() {
    _event = InputEvent::NONE;
}

void InputManager::handleButtonEvent(InputEvent ev) {
    _button.clear_event();
    _event = ev;
    _last_event = ev;
}
