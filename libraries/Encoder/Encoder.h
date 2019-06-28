#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#define PPR 390

class Encoder{
  private:
    int motorSide;     // left: -1, right: 1

    // pin
    int interruptPin;
    int directionPin;

    // others
    int ppr;           // wheel angle (PPR)
    float angle;       // wheel angle (rad)
    float speed;       // wheel speed (rad/s)


  public:
    // constructor
    Encoder();

    // set funciton
    void setMotorSide(const int side);
    void setPin(const int interruptPin, const int directionPin);

    // get function
    int getInterruptPin();
    float getAngle();
    float getSpeed();
    
    // update fuction
    void updatePPR();   // interrupt 
    void update(const float samplingTime);
    
    // reset function
    void reset();       // clear state
};

#endif //ENCODER_H
