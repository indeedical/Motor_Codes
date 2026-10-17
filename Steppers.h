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

    void runstepperforward(int steps, int delayTime) {//The speed of the stepper motor is controlled by the delayTime parameter. A smaller value results in a faster speed, while a larger value results in a slower speed.
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

class TB6600 {
    int _enablepin;
    int _pulsepin;
    int _dirpin;

    // Constructor: Saves the pin numbers
    TB6600(int enb, int pul, int dir) {
        _enablepin = enb;
        _pulsepin  = pul;
        _dirpin    = dir;
    }

    // Call this in your setup()
    void begin() {
        pinMode(_enablepin, OUTPUT);
        pinMode(_pulsepin, OUTPUT);
        pinMode(_dirpin, OUTPUT);

        // LOW enables the TB6600 driver
        digitalWrite(_enablepin, LOW);
        digitalWrite(_pulsepin, LOW);
        digitalWrite(_dirpin, HIGH);
    }

    // Move forward (DIR is HIGH), runs for given number of steps, then stops
    void runstepperforward(int steps, int delayTime) {
        digitalWrite(_enablepin, LOW);   // Make sure motor is ON
        digitalWrite(_dirpin, HIGH);     // Forward direction

        for (int i = 0; i < steps; i++) {
            digitalWrite(_pulsepin, HIGH);
            delayMicroseconds(delayTime);  // Smaller number = faster speed
            digitalWrite(_pulsepin, LOW);
            delayMicroseconds(delayTime);
        }
    }

    // Move reverse (DIR is LOW), runs for given number of steps, then stops
    void runstepperreverse(int steps, int delayTime) {
        digitalWrite(_enablepin, LOW);   // Make sure motor is ON
        digitalWrite(_dirpin, LOW);      // Reverse direction

        for (int i = 0; i < steps; i++) {
            digitalWrite(_pulsepin, HIGH);
            delayMicroseconds(delayTime);
            digitalWrite(_pulsepin, LOW);
            delayMicroseconds(delayTime);
        }
    }

    // Cuts power to the motor coils so it stops and cools down
    void stop() {
        digitalWrite(_pulsepin, LOW);
        digitalWrite(_enablepin, HIGH);  // HIGH disables the TB6600
    }
};