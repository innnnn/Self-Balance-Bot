#include "BalancebotController.h"

// constructor
BalanceBotController::BalanceBotController(){
	MAX_OUTPUT = 0;
	MIN_OUTPUT = 0;
    Kp = 0;
    Ki = 0;
    Kd = 0;
    reference = 0;
}

// set function
void BalanceBotController::SetSaturation(const float max, const float min){
	MAX_OUTPUT = max;
	MIN_OUTPUT = min;
}

void BalanceBotController::SetPID(const float Kp, const float Ki, const float Kd){
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
}

void BalanceBotController::SetReference(const float reference){
    this->reference = reference;
}

// get function
String BalanceBotController::GetInformation(){
	return String(Kp, 1) + "," + String(Ki, 0) + "," + String(Kd, 2) + "," + String(reference, 3);
}

float BalanceBotController::GetReference(){
	return reference;
}

// update
float BalanceBotController::Update(const float feedback, const float dt){
    float error = reference - feedback;

    // Proportional termW
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

    return output;
}
