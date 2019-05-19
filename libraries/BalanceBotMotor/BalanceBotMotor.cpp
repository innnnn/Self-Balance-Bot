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

void BalanceBotMotor::SetDirectionPins( const int pinA, 
                                             const int pinB ){
	directionPinA = pinA;
	directionPinB = pinB;
	pinMode(directionPinA, OUTPUT);
	pinMode(directionPinB, OUTPUT);
}

void BalanceBotMotor::SetStandbyPin(const int pin){
    standbyPin = pin;
    pinMode(standbyPin, OUTPUT);
}

void BalanceBotMotor::SetSamplingTime(const float dt){
    this->dt = dt;
}

void BalanceBotMotor::SetEncoder(const int side,
                                 const int interruptPin, 
                                 const int directionPin){
    encoder.SetMotorSide(side);
    encoder.SetInterruptPin(interruptPin);
    encoder.SetDirectionPin(directionPin); 
    encoder.SetSamplingTime(this->dt);
}

void BalanceBotMotor::SetControlMode(int mode){
	controlMode = mode;
}

void BalanceBotMotor::SetPsiController(float kp, float ki, float kd, float reference){
    psiController.SetSamplingTime(dt);
    psiController.SetPID(kp, ki, kd);
    psiController.SetReference(reference);
}

void BalanceBotMotor::SetThetaController(float kp, float ki, float kd, float reference){
    thetaController.SetSamplingTime(dt);
    thetaController.SetPID(kp, ki, kd);
    thetaController.SetReference(reference);
}

void BalanceBotMotor::SetStateFeedbackController(float k1, float k2, float k3, float k4){
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

// update function
void BalanceBotMotor::UpdateAngle(){  // motor update
    angle = encoder.GetAngle();
}

void BalanceBotMotor::UpdateSpeed(){  // motor update
	speed = encoder.GetSpeed();
}

void BalanceBotMotor::UpdateControl(const float psi){  // motor update
	float output = 0.0;
	
	switch(controlMode){
		case 0:
			output = 0;
			break;
		case 1:
			output = -psiController.Update(psi);
			break;
		case 2:
			break;
		case 3:
			//output = stateFeedbackController.Update();
			break;
	}
	
    Rotate( (int)(output* voltage2Pwm) );
}

void BalanceBotMotor::UpdateEncoder(){  // interrupt
    encoder.Update();
}

void BalanceBotMotor::Update(const float psi){  // timer
    UpdateAngle();
    UpdateSpeed();
    UpdateControl(psi);
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
	// Saturation
	// Max output: 255
	// Min output: -255
	if(pwm > MAX_OUTPUT)
		pwm = MAX_OUTPUT;
	else if(pwm < MIN_OUTPUT)
		pwm = MIN_OUTPUT;
	
    //speed: 0 ~ 255
    //direction: -1-> clockwise, 1-> counter-clockwise
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
