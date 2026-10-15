#pragma once
#include <Arduino.h>

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