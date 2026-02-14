#pragma once
#include <Arduino.h>
#include <led.h>
#include <motor_controller.h>

class InputManager;

enum class RaceState {
    IDLE,
    READY,
    RUNNING,
    STOPPING,
};

class RaceController {
public:
    RaceController(
        InputManager& inputs, 
        uint8_t status_led_pin, 
        uint8_t status_led_2_pin
    );

    void begin();
    void update();

    RaceState get_state() const;

private:
    void handleIdle();
    void handleReady();
    void handleRunning();
    void handleStopping();

    void setState(RaceState newState);

    RaceState _state;
    InputManager& _inputs;
    Led _status_led;
    Led _status_led_2;
};