// Goal: system id need constant 5v input 
const int voltage2Pwm = 255/12.0;

void StableVoltage_MotorInput(const int voltage){
    // voltage>0  --> move forward
    // voltage<0  --> move backward
    LeftMotorMove ( voltage * voltage2Pwm );
    RightMotorMove( voltage * voltage2Pwm );
} 
