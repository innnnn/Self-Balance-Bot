#ifndef BALANBOTENCODER_H
#define BALANBOTENCODER_H

#include <Arduino.h>
#define PPR 390

class BalanbotEncoder{
  private:
    int mInterruptPin;
    int mDirectionPin;
    int mPosition;
    float speed;
    int lastPosition;
    float lastAngle;
    float *pre_v;  //save previous velocity data
   
  public:
    BalanbotEncoder(); 
    void SetInterruptPin(const int pin);
    void SetDirectionPin(const int pin);
    void SetPosition(const int pos);
    //void SetPins();
    int GetInterruptPin();
    int GetDirectionPin();
    int GetPosition();
    int GetPPR();
    float GetSpeed(float dT);
    void ClearPosition();
    void Update();
};

#endif //BALANBOTENCODER_H