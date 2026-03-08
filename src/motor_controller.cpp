#include "motor_controller.h"

MotorController::MotorController(uint8_t l1, uint8_t l2, uint8_t ch1, uint8_t ch2, uint8_t r1, uint8_t r2, uint8_t ch3, uint8_t ch4)
    : motor_l(l1, l2, ch1, ch2), 
      motor_r(r1, r2, ch3, ch4), 
      _kp(0), 
      _ki(0), 
      _kd(0), 
      _last_error(0), 
      _integral(0), 
      _setpoint(0) {}

void MotorController::begin() {
    motor_l.begin();
    motor_r.begin();
}

void MotorController::set_pid(float p, float i, float d) {
    _kp = p; _ki = i; _kd = d;
}

void MotorController::set_target(float target) {
    _setpoint = target;
}

void MotorController::update(float current_value) {
    // float error = _setpoint - current_value;

    // float P = _kp * error;

    // _integral += error;
    // float I = _ki * _integral;

    // float D = _kd * (error - _last_error);
    // _last_error = error;

    // int16_t output = (int16_t)constrain(P + I + D, -255, 255);
    int16_t output = (int16_t)constrain(current_value, -255, 255);
    motor_l.drive(output);
    motor_r.drive(output);
}

void MotorController::stop() {
    motor_l.stop();
    motor_r.stop();
    _integral = 0; 
}