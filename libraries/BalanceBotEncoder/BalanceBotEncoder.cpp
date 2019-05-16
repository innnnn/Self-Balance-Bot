#include "BalanceBotEncoder.h"

// constructor
BalanceBotEncoder::BalanceBotEncoder(){
    position = 0;
    angle = 0;
    speed = 0;
}

// set function
void BalanceBotEncoder::SetMotorSide(const int side){
    motorSide = side;
}

void BalanceBotEncoder::SetInterruptPin(const int pin){
    interruptPin = pin;
}

void BalanceBotEncoder::SetDirectionPin(const int pin){
    directionPin = pin;
    pinMode(directionPin, INPUT);
}

void BalanceBotEncoder::SetSamplingTime(const float dt){
	this->dt = dt;
}

// get function
int BalanceBotEncoder::GetMotorSide(){
    return motorSide;
}

int BalanceBotEncoder::GetInterruptPin(){
    return interruptPin;
}

int BalanceBotEncoder::GetDirectionPin(){
    return directionPin;
}

float BalanceBotEncoder::GetAngle(){
	return angle * motorSide;
}

float BalanceBotEncoder::GetSpeed(){
    return speed * motorSide;
}

// update function
void BalanceBotEncoder::Update(){  // interrupt
	digitalRead(directionPin) == HIGH ? position++ : position--;
	
	float newAngle = 2 * PI * ((float)position / (float)PPR);
    speed = (newAngle - angle) / dt;
    angle = newAngle;
}

// reset funciton
void BalanceBotEncoder::Reset(){
    position = 0;
    angle = 0;
    speed = 0;
}
