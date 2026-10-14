#pragma once
#include <Arduino.h>

class A4988{

    private:
        int _enablepin;
        int _pulepin;
        int _dirpin;
    
    public:
        A4988(int enb , int pls, int dir){
            int _enablepin = enb;
            int _pulepin = pul;
            int _dirpin = dir;

        }

        void begin(){
            pinmode(_enablepin, LOW);
            pinmode(_pulepin, LOW);
            pinmode(_dirpin, HIGH);
        }
        void runstepperforward(int steps , int delayTime = 800){
            digitalWrite(_dirpin, HIGH);
            digitalWrite(_enablepin, LOW);

            for (int i = 0; i < steps; i++) {
                digitalWrite(_pulsepin, HIGH);
                delayMicroseconds(delayTime);  // Smaller number = faster speed
                digitalWrite(_pulsepin, LOW);
                delayMicroseconds(delayTime);
            }
        }
        void runstepperreverse(int steps, in delayTime = 800){
            digitalWrite(_pulepin, LOW);
            digitalWrite(_dirpin, LOW);

            for (int i = 0; i < steps; i++) {
                digitalWrite(_pulsepin, HIGH);
                delayMicroseconds(delayTime);  // Smaller number = faster speed
                digitalWrite(_pulsepin, LOW);
                delayMicroseconds(delayTime);
            }
        }
        void stop(){
            digitalWrite(_pulepin, LOW);
            digitalWrite(_enablepin, HIGH);
        }
}