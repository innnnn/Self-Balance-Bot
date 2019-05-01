#include "BalanceBotEncoder.h"

BalanceBotEncoder::BalanceBotEncoder(){
    position = 0;
    lastAngle = 0;
}

void BalanceBotEncoder::SetInterruptPin(const int pin){
    interruptPin = pin;
}

void BalanceBotEncoder::SetDirectionPin(const int pin){
    directionPin = pin;
    pinMode(mDirectionPin, INPUT);
}

void BalanceBotEncoder::SetPosition(const int pos){
    position = pos;
}

void BalanceBotEncoder::SetSamplingTime(const float dt){
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
    float newAngle = 2 * PI * ((float)position / (float)PPR) * RAD_TO_DEG;
    speed = (newAngle - lastAngle) / dT;
    lastAngle = newAngle;
    return speed;
}

void BalanceBotEncoder::ClearPosition(){
    position = 0;
}

void BalanceBotEncoder::Update(){
	digitalRead(directionPin) == HIGH ? position++ : position--;
}
