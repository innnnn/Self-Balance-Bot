#include "BalancebotController.h"

PIDController::PIDController(){
	Kp = 0;
	Ki = 0;
	Kd = 0;
	reference = 0;
}

void PIDController::SetPID(const float Kp, const float Ki, const float Kd){
	this.Kp = Kp;
	this.Ki = Ki;
	this.Kd = Kd;
}

void PIDController::SetReference(const float reference){
	this.reference = reference;
}

void PIDController::SetSamplingTime(const float dt){
	this.dt = dt;
}

void PIDController::GetIfSteady(){
	if(preError < ERROR_TOLERANCE)
		return true;
	return false;
}

float PIDController::Update(float feedback){
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
	// Max output: 12v
	// Min output: -12v
	if(output > MAX_OUTPUT)
		output = MAX_OUTPUT;
	else if(output < MIN_OUTPUT)
		output = MIN_OUTPUT;
	
	// record the prevoius error
	preError = error;
	
 	return output;
}
