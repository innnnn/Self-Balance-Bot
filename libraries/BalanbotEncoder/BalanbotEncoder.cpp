#include "BalanbotEncoder.h"

BalanbotEncoder::BalanbotEncoder() :
    mInterruptPin (0),
    mDirectionPin (0),
    mPosition (0)
{
    pre_v = new float[5];
    pre_v[0] = 0;
    pre_v[1] = 0;
    pre_v[2] = 0;
    pre_v[3] = 0;
    pre_v[4] = 0;
    lastAngle = 0;
}

void BalanbotEncoder::SetInterruptPin(const int pin){
    mInterruptPin = pin;
}

void BalanbotEncoder::SetDirectionPin(const int pin){
    mDirectionPin = pin;
    pinMode(mDirectionPin, INPUT);
}

void BalanbotEncoder::SetPosition(const int pos){
    mPosition = pos;
}

int BalanbotEncoder::GetInterruptPin(){
    return mInterruptPin;
}

int BalanbotEncoder::GetDirectionPin(){
    return mDirectionPin;
}

int BalanbotEncoder::GetPosition(){
    return mPosition;
}

int BalanbotEncoder::GetPPR(){
    return PPR;
}

float BalanbotEncoder::GetSpeed(float dT){
    float newAngle = 2 * PI * ((float)mPosition / (float)PPR) * RAD_TO_DEG;
    speed = (newAngle - lastAngle) / dT;
    lastAngle = newAngle;
    // pre_v[4] = pre_v[3];
    // pre_v[3] = pre_v[2];
    // pre_v[2] = pre_v[1];
    // pre_v[1] = pre_v[0];
    // pre_v[0] = speed;

    // float avg_v = (pre_v[0] + pre_v[1] + pre_v[2] + pre_v[3] + pre_v[4]) / 5;
    // return (avg_v);
    return speed;
}

void BalanbotEncoder::ClearPosition(){
    mPosition = 0;
}

void BalanbotEncoder::Update(){
	if(digitalRead(mDirectionPin) == HIGH)
		mPosition++;
	else
		mPosition--;
}
