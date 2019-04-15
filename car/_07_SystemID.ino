// Goal: system id need constant 5v input 

void StableVoltage_MotorInput(const int voltage){
    // voltage>0  --> move forward
    // voltage<0  --> move backward
    LeftMotorMove ( 255 * (voltage / 12.0) );
    RightMotorMove( 255 * (voltage / 12.0) );
} 