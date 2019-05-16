#ifndef BALANCEBOTENCODER_H
#define BALANCEBOTENCODER_H

#include <Arduino.h>
#define PPR 390

class BalanceBotEncoder{
  private:
    int motorSide;
    // pin
    int interruptPin;
    int directionPin;
    
    // sampling time
    float dt;
    
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
    void SetSamplingTime(const float dt);
    
    // get function
    int GetMotorSide();
    int GetInterruptPin();
    int GetDirectionPin();
    float GetAngle();
    float GetSpeed();
    
    // update fuction
    void Update();
    
    // reset function
    void Reset();
};

#endif //BALANCEBOTENCODER_H
