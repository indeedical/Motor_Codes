#pragma once
#include "Arduino.h"

class BTN8962TA
{
    public:
    int ena= -1;
    int rpwmA= -1;
    int lpwmA=-1;
    int enb= -1;
    int rpwmB= -1;
    int lpwmB=-1;
    
    void begin(int _rpwmA, int _rpwmB, int _lpwmA, int _lpwmB, int _ena, int _enb)
    {
        rpwmA= _rpwmA;
        rpwmB= _rpwmB;
        lpwmB= _lpwmB;
        lpwmA= _lpwmA;
        ena= _ena;
        enb= _enb;
        pinMode(rpwmA, OUTPUT);
        pinMode(rpwmB, OUTPUT);
        pinMode(lpwmA, OUTPUT);
        pinMode(lpwmB, OUTPUT);
        pinMode(ena, OUTPUT);
        pinMode(enb, OUTPUT);
        analogWriteResolution(14);
        analogWriteFrequency(rpwmA, 20000);
        analogWriteFrequency(rpwmB, 20000);
        analogWriteFrequency(lpwmA, 20000);
        analogWriteFrequency(lpwmB, 20000);
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
        analogWrite(rpwMB, 0);
        analogWrite(lpwmB, 0);
        analogWrite(lpwmA, 0);
    }

    void rundc(int speed)
    {
        if (speed<=16383 && speed>=-16383)
        {
            if (speed>0)
            {
                rundcfwdA(speed);
                rundcfwdB(speed);
            }
            else if (speed<0)
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
    int dir= -1;
    int pwm= -1; 
    void begin(int dirp, int pwmp)
    {
        dir=dirp;
        pwm= pwmp;
        pinMode(dir, OUTPUT);
        pinMode(pwm, OUTPUT);
        analogWriteResolution(14);
        analogWriteFrequency(pwm, 20000);
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
        if (speed<=16383 && speed>=-16383)
        {
            if (speed>0)
            {
                rundcfwd(speed);
            }
            else if (speed<0)
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
    int in1=-1;
    int in2=-1;
    int in3=-1;
    int in4=-1;
    int ena=-1;
    int enb=-1;

    void begin(int _in1, int _in2, int _in3, int _in4, int _ena, int _enb)
    {   in1= _in1;
        in2= _in2;
        in3= _in3;
        in4= _in4;
        ena= _ena;
        enb= _enb;
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
        pinMode(in3, OUTPUT);
        pinMode(in4, OUTPUT);
        pinMode(ena, OUTPUT);
        pinMode(enb, OUTPUT);
        analogWriteResolution(14);
        analogWriteFrequency(ena, 20000);
        analogWriteFrequency(enb, 20000);
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
        if (speed<=16383 && speed>=-16383)
        {
            if (speed>0)
            {
                rundcfwdA(speed);
                rundcfwdB(speed);
            }
            else if (speed<0)
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