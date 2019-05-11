#ifndef BALANCEBOTMOTOR_H
#define BALANCEBOTMOTOR_H

#include "BalanceBotEncoder.h"
#include "BalanceBotController.h"
#include "BalanceBotStateFeedbackController.h"
#include <Arduino.h>

class BalanceBotMotor{
  private:
    const float voltage2Pwm = 255/12.0;
    
    BalanceBotEncoder encoder; 
    BalanceBotController psiController;
    BalanceBotController thetaController;
    BalanceBotStateFeedbackController stateFeedbackController; 
    
	int pwmPin, directionPinA, directionPinB, standbyPin;
    float angle;
    float speed;
    float dt;           // sampling time
	int controlMode;    // 1: psi, 2: psi&theta, 3, state feedback
    
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
    void SetControlMode(int mode);
    void SetPsiController(float reference, float kp, float ki, float kd);
    void SetThetaController(float reference, float kp, float ki, float kd);
    void SetStateFeedbackController(float k1, float k2, float k3, float k4);
    
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
