#pragma once
#include "motor.h"
#include <Arduino.h>

class MotorController {
    private:
        Motor motor_l;
        Motor motor_r;

        float _kp, _ki, _kd;
        float _last_error;
        float _integral;
        float _setpoint;

    public:
        MotorController(
            uint8_t l1, 
            uint8_t l2, 
            uint8_t ch1, 
            uint8_t ch2, 
            uint8_t r1, 
            uint8_t r2, 
            uint8_t ch3, 
            uint8_t ch4); 
            
        void begin();
        void set_pid(float p, float i, float d);
        void set_target(float target);
        void update(float current_value);
        
        void stop();
};