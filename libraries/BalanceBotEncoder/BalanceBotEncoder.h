#ifndef BALANCEBOTENCODER_H
#define BALANCEBOTENCODER_H

#include <Arduino.h>
#define PPR 390

class BalanceBotEncoder{
  private:
    int motorSide;    // left: -1, right: 1
    // pin
    int interruptPin;
    int directionPin;
    
    // others
    int position;      // wheel angle (PPR)
    float angle;       // wheel angle (rad)
    float speed;       // wheel speed (rad/s)
    
   
  public:
    // constructor
    BalanceBotEncoder(); 

    // set funciton
    void SetMotorSide(const int side);
    void SetInterruptPin(const int pin);
    void SetDirectionPin(const int pin);
    
    // get function
    int GetMotorSide();
    int GetInterruptPin();
    float GetAngle();
    float GetSpeed();
    
    // update fuction
    void UpdatePosition();
    void Update(const float samplingTime);
    
    // reset function
    void Reset();
};

#endif //BALANCEBOTENCODER_H
