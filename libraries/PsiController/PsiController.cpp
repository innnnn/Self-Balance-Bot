#include "PsiController.h"

// constructor
PsiController::PsiController(){
    Kp = 0;
    Ki = 0;
    Kd = 0;
    reference = 0;
    integral = 0;
    preError = 0;
    steady = false;
}

// set function
void PsiController::setSaturation(const float max, const float min){
    MAX_OUTPUT = max;
    MIN_OUTPUT = min;
}

void PsiController::setToleratedError(const float error){
    toleratedError = error;
}

void PsiController::setPID(const float kp, const float ki, const float kd){
    Kp = kp;
    Ki = ki;
    Kd = kd;
}

void PsiController::setReference(const float reference){
    this->reference = reference;
}

// get function
bool PsiController::getSteady(){
    return steady;
}

String PsiController::getInformation(){
    return String(Kp, 1) + "," + String(Ki, 0) + "," + String(Kd, 2) + "," + String(reference, 3);
}

String PsiController::getErrorIntegral(){  // for debug
    return String(integral, 4);
}

// update
float PsiController::update(const float feedback, const float dt){
    float error = reference - feedback;

    // Proportional term
    float pOut = Kp * error;

    // Integral term
    integral += error * dt;
    float iOut = Ki * integral;

    // Derivative term
    float derivative = ( error-preError ) / dt;
    float dOut = Kd * derivative;

    // Total output
    float output = pOut + iOut + dOut;

    // Saturation
    if(output > MAX_OUTPUT)
        output = MAX_OUTPUT;
    else if(output < MIN_OUTPUT)
        output = MIN_OUTPUT;
	
    // record the prevoius error
    preError = error;

    // check stable or not
    steady = ( fabs(preError) < toleratedError )? true : false;

    return output;
}

void PsiController::clearIntegral(){
    integral = 0;
}
