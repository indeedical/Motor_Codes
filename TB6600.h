#pragma once
#include <Arduino.h>

class TB6600 {
  private:
    int _enablepin;
    int _pulsepin;
    int _dirpin;

  public:
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
    void runstepperforward(int steps, int delayTime = 800) {
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
    void runstepperreverse(int steps, int delayTime = 800) {
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
