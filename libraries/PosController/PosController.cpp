#include "PosController.h"

// constructor
PosController::PosController(){
    Kp = 0;
    reference = 0;
    steady = false;
}

// set function
void PosController::setSaturation(const float max, const float min){
    MAX_OUTPUT = max;
    MIN_OUTPUT = min;
}

void PosController::setToleratedError(const float error){
    toleratedError = error;
}

void PosController::setPID(const float kp){
    Kp = kp;
}

void PosController::setReference(const float reference){
    this->reference = reference;
}

// get function
bool PosController::getSteady(){
    return steady;
}

String PosController::getInformation(){
    return String(Kp, 1) + "," + String(reference, 3);
}

// update
float PosController::update(const float feedback, const float speed){
    float error = reference - feedback;

    // Proportional term
    float output = Kp * error;

    // check stable or not
    steady = ( fabs(error) < toleratedError )? true : false;

    /* 
	if( error>0 && steady && speed<0 )
		output *= 1.3;
	else if( error>0 && !steady && speed<0 )
	    output *= 1.5;
    */

    // Saturation
    if(output > MAX_OUTPUT)
        output = MAX_OUTPUT;
    else if(output < MIN_OUTPUT)
        output = MIN_OUTPUT;
    
    return output;
}
