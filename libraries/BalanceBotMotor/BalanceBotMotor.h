#ifndef BALANCEBOTMOTOR_H
#define BALANCEBOTMOTOR_H

#include "BalanceBotEncoder.h"
#include "BalanceBotController.h"
#include "BalanceBotStateFeedbackController.h"
#include <Arduino.h>

class BalanceBotMotor{
    const float voltage2Pwm = 255/12.0;
	const int MAX_OUTPUT = 255;
	const int MIN_OUTPUT = -255;
    
  private:
    BalanceBotEncoder encoder;
    
    // controller
    BalanceBotController psiController;
    BalanceBotController thetaController;
    BalanceBotStateFeedbackController stateFeedbackController;
    
    // pin
	int pwmPin;
	int directionPinA;
	int directionPinB;
	int standbyPin;
	
	// sampling time
	float dt;
	
	// others
    float angle;        // wheel angle (rad)
    float speed;        // wheel speed (rad/s)
	int controlMode;    // 0: nothing, 1: psi, 2: psi&theta, 3, state feedback
    
    // update function
    void UpdateAngle();
    void UpdateSpeed();
    void UpdateControl(const float psi);

  public:
  	// constructor
    BalanceBotMotor();
    
    // set function
    void SetPwmPin(const int pin);
    void SetDirectionPins( const int pinA, 
                                  const int pinB );
    void SetStandbyPin(const int pin);
    void SetSamplingTime(const float dt);
    void SetEncoder(const int side,
                    const int interruptPin, 
                    const int directionPin);
    void SetControlMode(int mode);
    void SetPsiController(float kp, float ki, float kd, float reference);
    void SetThetaController(float kp, float ki, float kd, float reference);
    void SetStateFeedbackController(float k1, float k2, float k3, float k4);
    
    // get funciton
    int GetEncoderInterruptPin();
    float GetSpeed();
    float GetAngle();
    
    // update function
	void UpdateEncoder();
    void Update(const float psi);
    
    // reset function
	void Reset();
	
    // others
    void Rotate(int pwm);
};

#endif /* BALANCEBOTMOTOR_H */
