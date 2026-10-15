#pragma once
#include <Arduino.h>

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