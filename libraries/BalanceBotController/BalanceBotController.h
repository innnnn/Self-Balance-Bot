#ifndef BALANCEBOTCONTROLLER_H
#define BALANCEBOTCONTROLLER_H

#include <Arduino.h>

class BalanceBotController{
    const float ERROR_TOLERANCE = 0.5;

  private:
	// sampling time
	float dt;

	// others
	float Kp, Ki, Kd;  // PID control
	float reference;   // desire output
	float integral;    // record the sum of previous error
	float preError;    // previous error

  public:
    // constructor
	BalanceBotController();

	// set function
	void SetSamplingTime(const float dT);
	void SetPID(const float Kp, const float Ki, const float Kd);
	void SetReference(const float reference);

	// get function
	bool GetIfSteady();

	// update
	float Update(const float feedback);
};

#endif //BALANCEBOTCONTROLLER_H
