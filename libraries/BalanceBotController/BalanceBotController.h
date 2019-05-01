#ifndef BALANCEBOTCONTROLLER_H
#define BALANCEBOTCONTROLLER_H

#include <NumericalTool.h>

class PIDController{
	const float ERROR_TOLERANCE = 0.5;
	const float MAX_OUTPUT = 12.0;
	const float MIN_OUTPUT = -12.0;

	private:
		bool steady;
		float dt;
		float reference;
		float Kp, Ki, Kd;  // PID control
		float integral;    // record the sum of previous error
		float preError;    // previous error
		Differentiator mDifferentiator;
    	Integrator mIntegrator;  

	public: 
		PIDController();
		void SetPID(const float Kp, const float Ki, const float Kd);
		void SetReference(const float reference); // the desire output
		void SetSamplingTime(const float dT);
		void GetIfSteady();
		float Update(float feedback);
};

#endif //BALANCEBOTCONTROLLER_H
