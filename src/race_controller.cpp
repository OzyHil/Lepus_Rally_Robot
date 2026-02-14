#include "race_controller.h"
#include "input_manager.h"

RaceController::RaceController(InputManager& inputs, uint8_t status_led_pin, uint8_t status_led_2_pin)
    : _state(RaceState::IDLE),
      _inputs(inputs),
      _status_led(status_led_pin),
      _status_led_2(status_led_2_pin)
      {}

void RaceController::begin() {
    _status_led.begin();
    _status_led_2.begin();
    _status_led.pwm(30); 
    _status_led_2.pwm(30); 
    setState(RaceState::IDLE);
}

void RaceController::update() {
    _status_led.update();
    _status_led_2.update();
    
    switch (_state) {
        case RaceState::IDLE:       handleIdle();       break;
        case RaceState::READY:      handleReady();      break;
        case RaceState::RUNNING:    handleRunning();    break;
        case RaceState::STOPPING:   handleStopping();   break;
        default: break;}
}

RaceState RaceController::get_state() const {
    return _state;
}

void RaceController::setState(RaceState newState) {
    _state = newState;

    switch (_state) {
        case RaceState::IDLE:
            _status_led.blink(100);
            _status_led_2.blink(100);
            break;
            
        case RaceState::READY:
            _status_led.off();
            _status_led_2.blink(100);
        break;
        
        case RaceState::RUNNING:
            _status_led.blink(100);
            _status_led_2.off();
            break;
            
            case RaceState::STOPPING:
            _status_led.blink(100);
        break;
        }
    }

void RaceController::handleIdle() {
    if (_inputs.get_event() == InputEvent::READY_BUTTON) {
        _inputs.clear_events();
        setState(RaceState::READY);
    }
}
    
void RaceController::handleReady() {
    InputEvent ev = _inputs.get_event();
    
    if (ev == InputEvent::OBSTACLE_TRIGGERED) {
        _inputs.clear_events();
        setState(RaceState::RUNNING);
    }
    else if (ev == InputEvent::RESET_BUTTON) {
        _inputs.clear_events();
        setState(RaceState::IDLE);
    }
}

void RaceController::handleRunning() {   
    InputEvent ev = _inputs.get_event();
    if (_inputs.get_event() == InputEvent::DISTANCE_APPROACHING) {
        _inputs.clear_events();
        setState(RaceState::STOPPING);
    }
    else if (ev == InputEvent::RESET_BUTTON) {
        _inputs.clear_events();
        setState(RaceState::IDLE);
    }
    
}

void RaceController::handleStopping() {
    if (_inputs.get_event() == InputEvent::DISTANCE_REACHED) {
        _inputs.clear_events();
        setState(RaceState::IDLE);
    }
}