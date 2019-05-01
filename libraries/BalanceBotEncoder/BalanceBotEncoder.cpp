#include "BalanceBotEncoder.h"

BalanceBotEncoder::BalanceBotEncoder(){
    mPosition = 0;
    lastAngle = 0;
}

void BalanceBotEncoder::SetInterruptPin(const int pin){
    mInterruptPin = pin;
}

void BalanceBotEncoder::SetDirectionPin(const int pin){
    mDirectionPin = pin;
    pinMode(mDirectionPin, INPUT);
}

void BalanceBotEncoder::SetPosition(const int pos){
    mPosition = pos;
}

void BalanceBotEncoder::SetSamplingTime(const float dT){
	this.dt = dt;
}

int BalanceBotEncoder::GetInterruptPin(){
    return interruptPin;
}

int BalanceBotEncoder::GetDirectionPin(){
    return directionPin;
}

int BalanceBotEncoder::GetPosition(){
    return position;
}

int BalanceBotEncoder::GetPPR(){
    return PPR;
}

float BalanceBotEncoder::GetSpeed(){
    float newAngle = 2 * PI * ((float)mPosition / (float)PPR) * RAD_TO_DEG;
    speed = (newAngle - lastAngle) / dT;
    lastAngle = newAngle;
    return speed;
}

void BalanceBotEncoder::ClearPosition(){
    position = 0;
}

void BalanceBotEncoder::Update(){
	digitalRead(mirectionPin) == HIGH ? position++ : position--;
}
