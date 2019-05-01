#include "BalanceBotMotor.h"

BalanceBotMotor::BalanceBotMotor(){
    directionCoefficient = 1.0;
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

void BalanceBotMotor::SetDirectionCoefficient(const float directionCoefficient){
	this.directionCoefficient = directionCoefficient;
}

void BalanceBotMotor::SetEncoderPins( const int interruptPin, 
                                    const int directionPin ){
    encoder.SetInterruptPin(interruptPin);
    encoder.SetDirectionPin(directionPin); 
}

void BalanceBotMotor::SetSamplingTime(const float dt){
    this.dt = dt;
    encoder.setSamplingTime(this.dt);
}

void BalanceBotMotor::SetControl(int mode, float reference){
  //TODO
}

// true: inverse
// false: remain state 
void BalanceBotMotor::InverseRotationDirectionDefinition(const bool ifInverse){
    directionCoefficient = ifInverse? -1.0 : 1.0;
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

void BalanceBotMotor::Rotate(const int pwm){
    //speed: 0 ~ 255
    //direction: 0-> clockwise, 1-> counter-clockwise
    boolean pin1 = LOW;   //initial rotate direction: clockwise
    boolean pin2 = HIGH;
    if(mDirectionCoefficient == 1){ // ??????
        pin1 = HIGH;
        pin2 = LOW;
    }

    digitalWrite(mStandbyPin, HIGH);
    digitalWrite(mDirectionPinA, pin1);
    digitalWrite(mDirectionPinB, pin2);
    analogWrite(mPwmPin, pwm);
    
    /*
    Serial.println(mPwmPin); 
    Serial.println(pwm); 
    Serial.println(mDirectionPinA); 
    Serial.println(pin1); 
    Serial.println(mDirectionPinB); 
    Serial.println(pin2); 
    */
}

void BalanceBotMotor::Brake(){
  //TODO
}

void BalanceBotMotor::UpdateAngle(){
    int encoderPosition = encoder.GetPosition();
    angle =  directionCoefficient
            * (2*PI)
            * ( static_cast<float>(encoderPosition)
              / static_cast<float>(encoder.GetPPR()) );
}

void BalanceBotMotor::UpdateSpeed(){
    ppeed = mDifferentiator.differential(mAngle);
}

void BalanceBotMotor::UpdateEncoder(){
    encoder.Update();
}

void BalanceBotMotor::UpdateControl(){
    //TODO
}

void BalanceBotMotor::Update(){
    UpdateAngle();
    UpdateSpeed();
    UpdateControl();
}
