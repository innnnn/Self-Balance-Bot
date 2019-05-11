#ifndef BALANCEBOTCONTROLLER_H
#define BALANCEBOTCONTROLLER_H

#include <Arduino.h>

class BalanceBotController{
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

	public: 
		BalanceBotController();
		void SetSamplingTime(const float dT);
		void SetReference(const float reference); // the desire output
		void SetPID(const float Kp, const float Ki, const float Kd);
		bool GetIfSteady();
		float Update(const float feedback);
};

#endif //BALANCEBOTCONTROLLER_H