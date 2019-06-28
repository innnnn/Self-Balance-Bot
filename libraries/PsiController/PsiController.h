#ifndef PSICONTROLLER_H
#define PSICONTROLLER_H

#include <Arduino.h>
#include <math.h>

class PsiController{
  private:
    float MAX_OUTPUT;
    float MIN_OUTPUT;
    float toleratedError;
	float Kp, Ki, Kd;  // PID control
    float reference;   // desire output
    float integral;    // record the sum of previous error
    float preError;    // previous error
    bool steady;       // check the system is steady or not


  public:
    // constructor
    PsiController();

    // set function
    void setSaturation(const float max, const float min);
    void setToleratedError(const float error);
    void setPID(const float kp, const float ki, const float kd);
    void setReference(const float reference);

    // get function
    String getInformation();
    String getErrorIntegral();

    // update
    float update(const float feedback, const float dt);

    // chech
    bool isSteady();

    // clear
    void  clearIntegral();
};

#endif //PSICONTROLLER_H
