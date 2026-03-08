#include <Arduino.h>
#include <input_manager.h>
#include <race_controller.h>
#include <motor_controller.h>

constexpr uint8_t ky032_pin = 34;

constexpr uint8_t status_led_pin = 5;

constexpr uint8_t button_pin = 19;

constexpr uint8_t motor_l_pin1 = 15;
constexpr uint8_t motor_l_pin2 = 2;
constexpr uint8_t motor_l_ch1 = 0;
constexpr uint8_t motor_l_ch2 = 1;

constexpr uint8_t motor_r_pin1 = 22;
constexpr uint8_t motor_r_pin2 = 23;
constexpr uint8_t motor_r_ch3 = 2;
constexpr uint8_t motor_r_ch4 = 3;

InputManager inputs(
  ky032_pin, 
  button_pin
);

MotorController motor_controller(
  motor_l_pin1, 
  motor_l_pin2,
  motor_l_ch1,
  motor_l_ch2, 
  motor_r_pin1, 
  motor_r_pin2,
  motor_r_ch3,
  motor_r_ch4
);

RaceController race(
  inputs, 
  status_led_pin, 
  motor_controller
);

void setup() {
  inputs.begin();
  race.begin();
}

void loop() {
  inputs.update();
  race.update();
}