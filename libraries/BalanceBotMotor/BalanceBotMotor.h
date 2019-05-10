#ifndef BALANCEBOTMOTOR_H
#define BALANCEBOTMOTOR_H

#include "BalanceBotEncoder.h"
#include "BalanceBotController.h"
#include <NumericalTool.h>
#include <Arduino.h>

class BalanceBotMotor{
  private:
    const float voltage2Pwm = 255/12.0;
    
    BalanceBotEncoder encoder; 
    Differentiator mDifferentiator;
    BalanceBotController psiController;
    
	  int pwmPin, directionPinA, directionPinB, standbyPin;
    float angle;
    float speed;
    float dt;           // sampling time
	  int controlMode;
    
    void UpdateAngle();
    void UpdateSpeed();
    void UpdateControl(const float psi);

  public:  
    BalanceBotMotor();
    
    void SetPwmPin(const int pin);
    void SetDirectionPins( const int pinA, 
                                  const int pinB );
    void SetStandbyPin(const int pin);
    void SetSamplingTime(const float dt);
    void SetEncoder(const int side,
                    const int interruptPin, 
                    const int directionPin);
    void SetControl(int mode, float reference);
    
    int GetEncoderInterruptPin();
    float GetSpeed();
    float GetAngle();
    
    void Rotate(int pwm);
    void Brake();
    void UpdateEncoder();
    void Update(const float psi);

    // PIDController angleController;
    // PIDController speedController;
};

#endif /* BALANCEBOTMOTOR_H */
