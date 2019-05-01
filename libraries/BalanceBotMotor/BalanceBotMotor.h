#ifndef BALANCEBOTMOTOR_H
#define BALANCEBOTMOTOR_H

#include "BalanceBotEncoder.h"
#include "BalanceBotController.h"
#include <NumericalTool.h>
#include <Arduino.h>

class BalanceBotMotor{
  private:
    BalanceBotEncoder encoder; 
    Differentiator mDifferentiator;
    float directionCoefficient;
    
	int pwmPin, directionPinA, directionPinB, standbyPin;
    float angle;
    float speed;
    float dt; // sampling time
	int controlMode;
    
    void UpdateAngle();
    void UpdateSpeed();
    void UpdateControl();

  public:  
    BalanceBotMotor();
    
    void SetPwmPin(const int pin);
    void SetDirectionPins( const int pinA, 
                                  const int pinB );
    void SetStandbyPin(const int pin);
    void SetDirectionCoefficient(const float directionCoefficient);
    void SetEncoderPins(const int interruptPin, 
                        const int directionPin);
    void SetSamplingTime(const float dt);
    void SetControl(int mode, float reference);
    
    void InverseRotationDirectionDefinition(const bool ifInverse);
    
    int GetEncoderInterruptPin();
    float GetSpeed();
    float GetAngle();
    
    void Rotate(const int pwm);
    void Brake();
    void UpdateEncoder();
    void Update();

    PIDController angleController;
    PIDController speedController;
};

#endif /* BALANCEBOTMOTOR_H */
