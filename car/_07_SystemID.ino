// Goal: system id need constant 5v input

void StableVoltage(const int voltage){
    // voltage>0  --> move forward
    // voltage<0  --> move backward
    LeftMotorMove ( voltage * voltage2Pwm );
    RightMotorMove( voltage * voltage2Pwm );
}
