#include "Encoder.h"

// constructor
Encoder::Encoder(){
    ppr = 0;
    angle = 0;
    speed = 0;
}

// set function
void Encoder::setMotorSide(const int side){
    motorSide = side;
}

void Encoder::setPin(const int interruptPin, const int directionPin){
    this->interruptPin = interruptPin;
    
    this->directionPin = directionPin;
    pinMode(this->directionPin, INPUT);
}

// get function
int Encoder::getInterruptPin(){
    return interruptPin;
}

float Encoder::getAngle(){
    return angle * motorSide;
}

float Encoder::getSpeed(){
    return speed * motorSide;
}

// update function
void Encoder::updatePPR(){  // interrupt
    digitalRead(directionPin) == HIGH ? ppr++ : ppr--;
}

void Encoder::update(const float samplingTime){
    float newAngle = 2 * PI * ((float)ppr / (float)PPR);
    speed = (newAngle - angle) / samplingTime;

    angle = newAngle;
}

// reset funciton
void Encoder::reset(){
    ppr = 0;
    angle = 0;
    speed = 0;
}
