// Goal: system id need constant 5v input

void StableVoltage(const int voltage){
    // voltage>0  --> move forward
    // voltage<0  --> move backward
    motor_A.Rotate( voltage * 255/12.0 );  // bug!! need to fix
    motor_B.Rotate( voltage * 255/12.0 );  // want to use static constant
}

//temp
    // float speed_L = motor_A.GetSpeed();
    // float speed_R = motor_B.GetSpeed();
    // float psi = GetPsi();
    // String data = String(speed_L) + "," + String(speed_R) + ", " + String(psi);
    //Serial.println(data);
