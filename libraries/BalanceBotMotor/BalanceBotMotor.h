#ifndef BALANCEBOTMOTOR_H
#define BALANCEBOTMOTOR_H

#include "BalanceBotEncoder.h"
#include "BalanceBotController.h"
#include "BalanceBotStateFeedbackController.h"
#include <Arduino.h>

class BalanceBotMotor{
    // constant
    const float voltage2Pwm = 255/12.0;

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

	// others
    float angle;        // wheel angle (rad)
    float speed;        // wheel speed (rad/s)
    int controlMode;    // 0: nothing, 1: psi, 2: psi&theta, 3, state feedback

    // update function
    void UpdateAngle();
    void UpdateSpeed();
    void UpdateControl(const float psi,
	                   const float samplingTime);


  public:
    
	// constructor
    BalanceBotMotor();

    // set function
    void SetPwmPin(const int pin);
    void SetDirectionPins(const int pinA,
                          const int pinB);
    void SetStandbyPin(const int pin);
    void SetEncoder(const int side,
                    const int interruptPin, 
                    const int directionPin);
    void SetControllerSaturation();
    void SetControlMode(const int mode);
    void SetPsiController(const float kp,
	                      const float ki,
						  const float kd,
						  const float reference);
    void SetThetaController(const float kp,
	                        const float ki,
							const float kd,
							const float reference);
    void SetStateFeedbackController(const float k1,
	                                const float k2,
									const float k3,
									const float k4);

    // get funciton
    int GetEncoderInterruptPin();
    float GetSpeed();
    float GetAngle();

    // update function
    void UpdateEncoder();
    void Update(const float psi, const float samplingTime);

    // reset function
    void Reset();

    // others
    void Rotate(int pwm);
};

#endif /* BALANCEBOTMOTOR_H */
