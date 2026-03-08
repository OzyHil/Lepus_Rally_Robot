#pragma once
#include <Arduino.h>
#include <stdint.h>

class Motor {
private:
    uint8_t in1_pin;
    uint8_t in2_pin;

    uint8_t pwm_channel1;
    uint8_t pwm_channel2;

    uint8_t deadzone;

public:
    Motor(uint8_t in1, uint8_t in2, uint8_t ch1, uint8_t ch2);

    void begin();
    void drive(int16_t pwm_value);
    void set_deadzone(uint8_t dz);
    void stop();
    void brake();
};