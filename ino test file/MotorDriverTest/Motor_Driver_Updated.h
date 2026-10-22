#pragma once
#include "Arduino.h"
#ifndef maximumpwm
#define maximumpwm 255
#endif


class BTN8962TA
{
public:
    int ena = -1;
    int rpwmA = -1;
    int lpwmA = -1;
    int enb = -1;
    int rpwmB = -1;
    int lpwmB = -1;
    int maxpwm = maximumpwm;

    void begin(int _rpwmA, int _rpwmB, int _lpwmA, int _lpwmB, int _ena, int _enb, int _maxpwm = maximumpwm)
    {
        rpwmA = _rpwmA;
        rpwmB = _rpwmB;
        lpwmA = _lpwmA;
        lpwmB = _lpwmB;
        ena = _ena;
        enb = _enb;
        maxpwm = _maxpwm;

        pinMode(rpwmA, OUTPUT);
        pinMode(rpwmB, OUTPUT);
        pinMode(lpwmA, OUTPUT);
        pinMode(lpwmB, OUTPUT);
        pinMode(ena, OUTPUT);
        pinMode(enb, OUTPUT);

        // Enable the driver channels
        digitalWrite(ena, HIGH);
        digitalWrite(enb, HIGH);

        stopmotor();
    }

    void rundcfwdA(int speed)
    {
        analogWrite(lpwmA, 0);
        analogWrite(rpwmA, speed);
    }

    void rundcrevA(int speed)
    {
        analogWrite(rpwmA, 0);
        analogWrite(lpwmA, speed);
    }

    void rundcfwdB(int speed)
    {
        analogWrite(lpwmB, 0);
        analogWrite(rpwmB, speed);
    }

    void rundcrevB(int speed)
    {
        analogWrite(rpwmB, 0);
        analogWrite(lpwmB, speed);
    }

    void stopmotor()
    {
        analogWrite(rpwmA, 0);
        analogWrite(rpwmB, 0);
        analogWrite(lpwmB, 0);
        analogWrite(lpwmA, 0);
    }

    void rundc(int speed)
    {
        if (speed <= maxpwm && speed >= -maxpwm)
        {
            if (speed > 0)
            {
                rundcfwdA(speed);
                rundcfwdB(speed);
            }
            else if (speed < 0)
            {
                rundcrevA(-speed);
                rundcrevB(-speed);
            }
            else
            {
                stopmotor();
            }
        }
    }
};

class CyctronMDD20
{
public:
    int dir = -1;
    int pwm = -1;
    int maxpwm = maximumpwm;

    void begin(int dirp, int pwmp, int _maxpwm = maximumpwm)
    {
        dir = dirp;
        pwm = pwmp;
        maxpwm = _maxpwm;

        pinMode(dir, OUTPUT);
        pinMode(pwm, OUTPUT);

        stopmotor();
    }

    void rundcfwd(int speed)
    {
        digitalWrite(dir, HIGH);
        analogWrite(pwm, speed);
    }

    void rundcrev(int speed)
    {
        digitalWrite(dir, LOW);
        analogWrite(pwm, speed);
    }

    void runmotor(int speed)
    {
        if (speed <= maxpwm && speed >= -maxpwm)
        {
            if (speed > 0)
            {
                rundcfwd(speed);
            }
            else if (speed < 0)
            {
                rundcrev(-speed);
            }
            else
            {
                stopmotor();
            }
        }
    }

    void stopmotor()
    {
        analogWrite(pwm, 0);
    }
};

class L298N
{
public:
    int in1 = -1;
    int in2 = -1;
    int in3 = -1;
    int in4 = -1;
    int ena = -1;
    int enb = -1;
    int maxpwm = maximumpwm;

    void begin(int _in1, int _in2, int _in3, int _in4, int _ena, int _enb, int _maxpwm = maximumpwm)
    {
        in1 = _in1;
        in2 = _in2;
        in3 = _in3;
        in4 = _in4;
        ena = _ena;
        enb = _enb;
        maxpwm = _maxpwm;

        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
        pinMode(in3, OUTPUT);
        pinMode(in4, OUTPUT);
        pinMode(ena, OUTPUT);
        pinMode(enb, OUTPUT);

        stopmotor();
    }

    void rundcfwdA(int speed)
    {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(ena, speed);
    }

    void rundcrevA(int speed)
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(ena, speed);
    }

    void rundcfwdB(int speed)
    {
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(enb, speed);
    }

    void rundcrevB(int speed)
    {
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(enb, speed);
    }

    void stopmotor()
    {
        analogWrite(ena, 0);
        analogWrite(enb, 0);
    }

    void runmotors(int speed)
    {
        if (speed <= maxpwm && speed >= -maxpwm)
        {
            if (speed > 0)
            {
                rundcfwdA(speed);
                rundcfwdB(speed);
            }
            else if (speed < 0)
            {
                rundcrevA(-speed);
                rundcrevB(-speed);
            }
            else
            {
                stopmotor();
            }
        }
    }
};
void chooseMicrocontroller(int choice, int pwmPin = -1)
{
    if (choice == 1)
    {
        #if defined(ARDUINO)
        analogWriteResolution(pwmPin, 8);
        #endif
    }
    else if (choice == 2)
    {
        #if defined(ESP32)
        if (pwmPin >= 0) {
            analogWriteResolution(pwmPin, 12);
        }
        #endif
    }
    else if (choice == 3)
    {
        #if defined(TEENSYDUINO)
        analogWriteResolution(14);
        if (pwmPin >= 0) {
            analogWriteFrequency(pwmPin, 20000);
        }
        #endif
    }
}