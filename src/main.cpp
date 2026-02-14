#include <Arduino.h>
#include <input_manager.h>
#include <race_controller.h>

constexpr uint8_t ky032_pin  = 32;
constexpr uint8_t status_led_pin = 12;
constexpr uint8_t status_led_2_pin = 27;
constexpr uint8_t button_pin = 35;

InputManager inputs(
  ky032_pin, 
  button_pin
);

RaceController race(
  inputs, 
  status_led_pin, 
  status_led_2_pin
);

void setup() {
  inputs.begin();
  race.begin();
}

void loop() {
  inputs.update();
  race.update();
}