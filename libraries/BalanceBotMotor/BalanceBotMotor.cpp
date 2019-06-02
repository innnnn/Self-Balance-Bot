#include "BalanceBotMotor.h"

// constructor
BalanceBotMotor::BalanceBotMotor(){
    angle = 0.0;
    speed = 0.0;
    controlMode = 0;
}

// set function
void BalanceBotMotor::SetPwmPin(const int pin){
    pwmPin = pin;
    pinMode(pwmPin, OUTPUT);
}

void BalanceBotMotor::SetDirectionPins(const int pinA,
                                       const int pinB){
	directionPinA = pinA;
	directionPinB = pinB;
	pinMode(directionPinA, OUTPUT);
	pinMode(directionPinB, OUTPUT);
}

void BalanceBotMotor::SetStandbyPin(const int pin){
    standbyPin = pin;
    pinMode(standbyPin, OUTPUT);
}

void BalanceBotMotor::SetEncoder(const int side,
                                 const int interruptPin,
                                 const int directionPin){
    encoder.SetMotorSide(side);
    encoder.SetInterruptPin(interruptPin);
    encoder.SetDirectionPin(directionPin);
}

void BalanceBotMotor::SetControllerSaturation(){
	psiController.SetSaturation(12.0, -12.0);     // voltage : 12 ~ -12 (v)
	thetaController.SetSaturation(0.02, -0.02);   // theta : 0.02 ~ -0.02 (rad) or (1.1459 ~ -1.1459(degree))
}

void BalanceBotMotor::SetControlMode(int mode){
	controlMode = mode;
}

void BalanceBotMotor::SetPsiController(const float kp,
                                       const float ki,
									   const float kd,
									   const float reference){
    psiController.SetPID(kp, ki, kd);
    psiController.SetReference(reference);
}

void BalanceBotMotor::SetThetaController(const float kp,
                                         const float ki,
										 const float kd,
										 const float reference){
    thetaController.SetPID(kp, ki, kd);
    thetaController.SetReference(reference);
}

void BalanceBotMotor::SetStateFeedbackController(const float k1,
                                                 const float k2,
												 const float k3,
												 const float k4){
	stateFeedbackController.SetK(k1, k2, k3, k4);
}

// get funciton
int BalanceBotMotor::GetEncoderInterruptPin(){
  	return encoder.GetInterruptPin();
}

float BalanceBotMotor::GetSpeed(){
  	return speed;
} 

float BalanceBotMotor::GetAngle() {
  	return angle;
}

int BalanceBotMotor::GetControlleMode(){
	return controlMode;
}

String BalanceBotMotor::GetPsiControllerInformation(){
	return psiController.GetInformation();
}

String BalanceBotMotor::GetThetaControllerInformation(){
	return thetaController.GetInformation();
}

// update function
void BalanceBotMotor::UpdateAngle(){  // motor update
    angle = encoder.GetAngle();
}

void BalanceBotMotor::UpdateSpeed(){  // motor update
	speed = encoder.GetSpeed();
}

void BalanceBotMotor::UpdateControl(const float psi,
                                    const float samplingTime){  // motor update
	float output = 0.0;
	float desire_psi;
	
	switch(controlMode){
		case 0:
			output = 0;
			break;
		case 1:
			output = -psiController.Update(psi, samplingTime);
			break;
		case 2:
			desire_psi = thetaController.Update(angle, samplingTime);
			//Serial.println(desire_psi);
			output = -psiController.Update(desire_psi + psi, samplingTime);
			//Serial.println(output);
			break;
		case 3:
			//output = stateFeedbackController.Update();
			break;
	}
	
    Rotate( (int)(output* voltage2Pwm) );
}

void BalanceBotMotor::UpdateEncoder(){  // interrupt
    encoder.UpdatePosition();
}

void BalanceBotMotor::Update(const float psi, const float samplingTime){  // loop function
    encoder.Update(samplingTime);
	UpdateAngle();
    UpdateSpeed();
    UpdateControl(psi, samplingTime);
}

// reset function
void BalanceBotMotor::Reset(){
	angle = 0.0;
    speed = 0.0;
    controlMode = 0;
    
    encoder.Reset();
}

// others
void BalanceBotMotor::Rotate(int pwm){
    // pwm: 0 ~ 255
    // direction: -1-> clockwise, 1-> counter-clockwise
    boolean pin1 = LOW;   //initial rotate direction: clockwise
    boolean pin2 = HIGH;
    if(pwm < 0){
        pin1 = HIGH;
        pin2 = LOW;
        pwm = -pwm;
    }

    digitalWrite(standbyPin, HIGH);
    digitalWrite(directionPinA, pin1);
    digitalWrite(directionPinB, pin2);
    analogWrite(pwmPin, pwm);
}
