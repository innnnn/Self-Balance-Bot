#ifndef BALANCEBOTENCODER_H
#define BALANCEBOTENCODER_H

#include <Arduino.h>
#define PPR 390

class BalanceBotEncoder{
  private:
    int motorSide;
    int interruptPin;
    int directionPin;
    int position;

    float dt;
    float speed;

    float lastAngle;
   
  public:
    BalanceBotEncoder(); 
    void SetMotorSide(const int side);
    void SetInterruptPin(const int pin);
    void SetDirectionPin(const int pin);
    void SetPosition(const int pos);
    void SetSamplingTime(const float dt);
    
    int GetMotorSide();
    int GetInterruptPin();
    int GetDirectionPin();
    int GetPosition();
    float GetSpeed();
    int GetPPR();
    void ClearPosition();
    void Update();
};

#endif //BALANCEBOTENCODER_H
