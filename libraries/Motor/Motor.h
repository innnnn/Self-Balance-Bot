#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor{
  private:
    // pin
    int pwmPin;
    int directionPinA;
    int directionPinB;
    int standbyPin;


  public:
    // constructor
    Motor();

    // set function
    void setPin(const int pwmPin,
                const int directionPinA,
                const int directionPinB,
                const int standbyPin);

    // others
    void rotate(float voltage);
};

#endif // MOTOR_H 
