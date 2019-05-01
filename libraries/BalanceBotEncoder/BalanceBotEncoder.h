#ifndef BALANCEBOTENCODER_H
#define BALANCEBOTENCODER_H

#include <Arduino.h>
#define PPR 390

class BalanceBotEncoder{
  private:
    int interruptPin;
    int directionPin;
    int position;
    float speed;
	float samplingTime;
    float lastAngle;
   
  public:
    BalanceBotEncoder(); 
    void SetInterruptPin(const int pin);
    void SetDirectionPin(const int pin);
    void SetPosition(const int pos);
    void SetSamplingTime(const float dT);
    
    int GetInterruptPin();
    int GetDirectionPin();
    int GetPosition();
    int GetPPR();
    float GetSpeed();
    void ClearPosition();
    void Update();
};

#endif //BALANCEBOTENCODER_H
