#include "BalanceBotEncoder.h"

BalanceBotEncoder::BalanceBotEncoder(){
    position = 0;
    lastAngle = 0;
}

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

void BalanceBotEncoder::SetPosition(const int pos){
    position = pos;
}

void BalanceBotEncoder::SetSamplingTime(const float dt){
	this->dt = dt;
}

int BalanceBotEncoder::GetMotorSide(){
    return motorSide;
}

int BalanceBotEncoder::GetInterruptPin(){
    return interruptPin;
}

int BalanceBotEncoder::GetDirectionPin(){
    return directionPin;
}

int BalanceBotEncoder::GetPosition(){
    return position * motorSide;
}

float BalanceBotEncoder::GetSpeed(){
    float newAngle = 2 * PI * ((float)position / (float)PPR) * RAD_TO_DEG;
    speed = (newAngle - lastAngle) / dt;
    lastAngle = newAngle;
    return speed * motorSide;
}

int BalanceBotEncoder::GetPPR(){
    return PPR;
}

void BalanceBotEncoder::ClearPosition(){
    position = 0;
}

void BalanceBotEncoder::Update(){
	digitalRead(directionPin) == HIGH ? position++ : position--;
}