#include "motor.h"

Motor::Motor(uint8_t in1, uint8_t in2, uint8_t ch1, uint8_t ch2)
    : in1_pin(in1), in2_pin(in2),
      pwm_channel1(ch1), pwm_channel2(ch2),
      deadzone(0) {}

void Motor::begin() {

    pinMode(in1_pin, OUTPUT);
    pinMode(in2_pin, OUTPUT);

    ledcSetup(pwm_channel1, 2000, 8);
    ledcSetup(pwm_channel2, 2000, 8);

    ledcAttachPin(in1_pin, pwm_channel1);
    ledcAttachPin(in2_pin, pwm_channel2);

    stop();
}

void Motor::set_deadzone(uint8_t dz) {
    deadzone = dz;
}

void Motor::drive(int16_t pwm_value) {

    if (abs(pwm_value) < deadzone) {
        stop();
        return;
    }

    int16_t power = constrain(pwm_value, -255, 255);

    if (power > 0) {
        ledcWrite(pwm_channel1, power);
        ledcWrite(pwm_channel2, 0);
    }
    else if (power < 0) {
        ledcWrite(pwm_channel1, 0);
        ledcWrite(pwm_channel2, abs(power));
    }
    else {
        stop();
    }
}

void Motor::stop() {
    ledcWrite(pwm_channel1, 0);
    ledcWrite(pwm_channel2, 0);
}

void Motor::brake() {
    ledcWrite(pwm_channel1, 255);
    ledcWrite(pwm_channel2, 255);
}