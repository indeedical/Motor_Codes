#include "CytronMDD20.h"

const int m1d = 0, m1p = 0;

CytronMDD20 m1;

void setup() 
{
  Serial.begin(115200);
  m1.begin(m1d,m1p);
}

void loop() 
{
  //testing each motor
  m1.runmotor(5000);
  delay(2000);
  m1.stopmotor();
  delay(2000);
}