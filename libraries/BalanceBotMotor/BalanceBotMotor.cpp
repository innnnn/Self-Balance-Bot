#include "BalanceBotMotor.h"

BalanceBotMotor::BalanceBotMotor(){
    angle = 0.0;
    speed = 0.0;
    controlMode = 0;
}

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

void BalanceBotMotor::SetControl(int mode, float reference){
    psiController.SetSamplingTime(dt);
    psiController.SetPID(0, 0, 0);     //TODO
    psiController.SetReference(0);
}

int BalanceBotMotor::GetEncoderInterruptPin(){
  	return encoder.GetInterruptPin();
}

float BalanceBotMotor::GetSpeed(){
    speed = encoder.GetSpeed();
  	return speed;
} 

float BalanceBotMotor::GetAngle() {
  	return angle;
}

void BalanceBotMotor::Rotate(int pwm){
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
    
    /*
    Serial.println(pwmPin);
    Serial.println(pwm); 
    Serial.println(directionPinA); 
    Serial.println(pin1); 
    Serial.println(directionPinB); 
    Serial.println(pin2); 
    */
}

void BalanceBotMotor::Brake(){
  //TODO
}

void BalanceBotMotor::UpdateAngle(){
    int encoderPosition = encoder.GetPosition();
    angle = (2*PI)
            * ( static_cast<float>(encoderPosition)
              / static_cast<float>(encoder.GetPPR()));
}

void BalanceBotMotor::UpdateSpeed(){
    speed = mDifferentiator.differential(angle);
}

void BalanceBotMotor::UpdateEncoder(){
    encoder.Update();
}

void BalanceBotMotor::UpdateControl(const float psi){
    //TODO
    float voltage = psiController.Update(psi);
    Rotate(voltage * voltage2Pwm);
}

void BalanceBotMotor::Update(const float psi){
    UpdateAngle();
    UpdateSpeed();
    UpdateControl(psi);
}
