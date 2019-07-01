#ifndef POSCONTROLLER_H
#define POSCONTROLLER_H

#include <Arduino.h>
#include <math.h>

class PosController{
  private:
    float MAX_OUTPUT;
    float MIN_OUTPUT;
    float toleratedError;
    float Kp;          // PID control
    float reference;   // desire output
    bool steady;       // check the system is steady or not


  public:
    // constructor
    PosController();

    // set function
    void setSaturation(const float max, const float min);
    void setToleratedError(const float error);
    void setPID(const float kp);
    void setReference(const float reference);

    // get function
    String getInformation();

    // update
    float update(const float feedback);

    // chech
    bool isSteady();
};

#endif //POSCONTROLLER_H
