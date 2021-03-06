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
bool PhiController::getSteady(){
    return steady;
}

String PhiController::getInformation(){
    return String(Kp, 1) + "," + String(reference, 3);
}

// update
float PhiController::update(const float feedback){
    float error = reference - feedback;

    // Proportional term
    float output = Kp * error;

    // Saturation
    if(output > MAX_OUTPUT)
        output = MAX_OUTPUT;
    else if(output < MIN_OUTPUT)
        output = MIN_OUTPUT;

    // check stable or not
    steady = ( fabs(error) < toleratedError )? true : false;

    return output;
}
