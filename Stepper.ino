#include <Arduino.h>
#include "Steppers.h"

// ESP32 Pins
const int EN_PIN  = 18;  // ENA
const int PUL_PIN = 19;  // PUL / STEP
const int DIR_PIN = 21;  // DIR

// Choose which driver you are testing (uncomment the one you want):
TB6600 stepper(EN_PIN, PUL_PIN, DIR_PIN);
// A4988 stepper(EN_PIN, PUL_PIN, DIR_PIN);

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("ESP32 Stepper Test Started!");

    stepper.begin();
}

void loop() {
    Serial.println("Moving Forward...");
    stepper.runstepperforward(400, 800); // (steps, delayMicroseconds)
    delay(1000);

    Serial.println("Moving Reverse...");
    stepper.runstepperreverse(400, 800);
    delay(1000);

    Serial.println("Stopped (holding torque OFF)...");
    stepper.stop();
    delay(3000);
}