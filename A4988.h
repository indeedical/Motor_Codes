#pragma once
#include <Arduino.h>

class A4988 {
    int _enablepin;
    int _pulsepin;
    int _dirpin;

    // Constructor to set pins
    A4988(int enb, int pul, int dir) {
        _enablepin = enb;
        _pulsepin  = pul;
        _dirpin    = dir;
    }

    void begin() {
        pinMode(_enablepin, OUTPUT);
        pinMode(_pulsepin, OUTPUT);
        pinMode(_dirpin, OUTPUT);

        digitalWrite(_enablepin, LOW);
        digitalWrite(_pulsepin, LOW);
        digitalWrite(_dirpin, HIGH);
    }

    void runstepperforward(int steps, int delayTime) {
        digitalWrite(_dirpin, HIGH);
        digitalWrite(_enablepin, LOW);

        for (int i = 0; i < steps; i++) {
            digitalWrite(_pulsepin, HIGH);
            delayMicroseconds(delayTime);
            digitalWrite(_pulsepin, LOW);
            delayMicroseconds(delayTime);
        }
    }

    void runstepperreverse(int steps, int delayTime) {
        digitalWrite(_enablepin, LOW);
        digitalWrite(_dirpin, LOW);

        for (int i = 0; i < steps; i++) {
            digitalWrite(_pulsepin, HIGH);
            delayMicroseconds(delayTime);
            digitalWrite(_pulsepin, LOW);
            delayMicroseconds(delayTime);
        }
    }

    void stop() {
        digitalWrite(_pulsepin, LOW);
        digitalWrite(_enablepin, HIGH);
    }
};