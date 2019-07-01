#ifndef PHICONTROLLER_H
#define PHICONTROLLER_H

#include <Arduino.h>
#include <math.h>

class PhiController{
  private:
    float MAX_OUTPUT;
    float MIN_OUTPUT;
    float toleratedError;
    float Kp;          // PID control
    float reference;   // desire output
    bool steady;       // check the system is steady or not

  public:
    // constructor
    PhiController();

    // set function
    void setSaturation(const float max, const float min);
    void setToleratedError(const float error);
    void setPID(const float kp);
    void setReference(const float reference);

    // get function
    bool getSteasy();
    String getInformation();

    // update
    float update(const float feedback);
};

#endif //PHICONTROLLER_H
