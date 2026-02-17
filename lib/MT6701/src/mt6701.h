#pragma once
#include <Arduino.h>

class Dual_MT6701 {
  private:
    int _clk, _data_esq, _data_dir;
    uint16_t _raw_esq, _raw_dir;
    uint16_t _last_raw_esq, _last_raw_dir;
    unsigned long _last_micros;
    float _rpm_esq, _rpm_dir;
    float _alpha;
    
    void readHardware();
    float compute_RPM(uint16_t current, uint16_t last, float dt, float current_rpm_val);

  public:
    Dual_MT6701(int clk_pin, int data_esq_pin, int data_dir_pin, float filter_alpha = 0.15);
    
    void begin();
    void update(); 
    
    float get_angle_esq();
    float get_angle_dir();
    float get_rpm_esq();
    float get_rpm_dir();
};