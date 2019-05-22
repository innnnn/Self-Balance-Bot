#ifndef BALANCEBOTCONTROLLER_H
#define BALANCEBOTCONTROLLER_H

#include <Arduino.h>

class BalanceBotController{
  private:
	float Kp, Ki, Kd;  // PID control
	float reference;   // desire output
	float integral;    // record the sum of previous error
	float preError;    // previous error


  public:
    // constructor
	BalanceBotController();

	// set function
	void SetPID(const float Kp, const float Ki, const float Kd);
	void SetReference(const float reference);

	// get function
	String GetPID();
	float GetReference();

	// update
	float Update(const float feedback, const float dt);
};

#endif //BALANCEBOTCONTROLLER_H
