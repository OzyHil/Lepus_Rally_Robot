#include "mt6701.h"

Dual_MT6701::Dual_MT6701(int clk_pin, int data_esq_pin, int data_dir_pin, float filter_alpha) {
    _clk = clk_pin;
    _data_esq = data_esq_pin;
    _data_dir = data_dir_pin;
    _alpha = filter_alpha;
    _raw_esq = _raw_dir = _last_raw_esq = _last_raw_dir = 0;
    _rpm_esq = _rpm_dir = 0;
}

void Dual_MT6701::begin() {
    pinMode(_clk, OUTPUT);
    pinMode(_data_esq, INPUT);
    pinMode(_data_dir, INPUT);
    digitalWrite(_clk, HIGH);
    _last_micros = micros();
}

void Dual_MT6701::readHardware() {
    _raw_esq = _raw_dir = 0;
    digitalWrite(_clk, LOW);
    for (int i = 0; i < 14; i++) {
        digitalWrite(_clk, HIGH); 
        if (digitalRead(_data_esq)) _raw_esq |= (1 << (13 - i));
        if (digitalRead(_data_dir)) _raw_dir |= (1 << (13 - i));
        digitalWrite(_clk, LOW);
    }
    digitalWrite(_clk, HIGH);
}

float Dual_MT6701::compute_RPM(uint16_t current, uint16_t last, float dt, float current_rpm_val) {
    int diff = current - last;
    
    // Trata a passagem do zero (wrap-around)
    if (diff > 8192) diff -= 16384;
    else if (diff < -8192) diff += 16384;

    float instantRPM = (diff / 16384.0) * 60.0 / dt;
    
    // Aplica o filtro EMA
    return (instantRPM * _alpha) + (current_rpm_val * (1.0 - _alpha));
}

void Dual_MT6701::update() {
    unsigned long now = micros();
    float dt = (now - _last_micros) / 1000000.0;

    if (dt < 0.0002) return; 

    readHardware();

    _rpm_esq = compute_RPM(_raw_esq, _last_raw_esq, dt, _rpm_esq);
    _rpm_dir = compute_RPM(_raw_dir, _last_raw_dir, dt, _rpm_dir);

    _last_raw_esq = _raw_esq;
    _last_raw_dir = _raw_dir;
    _last_micros = now;
}

float Dual_MT6701::get_angle_esq() { return (_raw_esq * 360.0) / 16384.0; }
float Dual_MT6701::get_angle_dir() { return (_raw_dir * 360.0) / 16384.0; }
float Dual_MT6701::get_rpm_esq()   { return _rpm_esq; }
float Dual_MT6701::get_rpm_dir()   { return _rpm_dir; }