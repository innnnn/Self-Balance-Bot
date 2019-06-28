#include "PhiController.h"

// constructor
PhiController::PhiController(){
    Kp = 0;
    reference = 0;
    steady = false;
}

// set function
void PhiController::setSaturation(const float max, const float min){
    MAX_OUTPUT = max;
    MIN_OUTPUT = min;
}

void PhiController::setToleratedError(const float error){
    toleratedError = error;
}

void PhiController::setPID(const float kp){
    Kp = kp;
}

void PhiController::setReference(const float reference){
    this->reference = reference;
}

// get function
String PhiController::getInformation(){
    return String(Kp, 1) + "," + String(reference, 3);
}

// update
float PhiController::update(const float feedback){
    float error = reference - feedback;

    // Proportional term
    float output = Kp * error;

    steady = ( abs(error) < toleratedError )? true : false;

    // Saturation
    if(output > MAX_OUTPUT)
        output = MAX_OUTPUT;
    else if(output < MIN_OUTPUT)
        output = MIN_OUTPUT;

    return output;
}

bool PhiController::isSteady(){
    return steady;
}
