// Goal: system id need constant 5v input

void StableVoltage(const int voltage){
    // voltage>0  --> move forward
    // voltage<0  --> move backward
    motor_A.Rotate ( voltage * voltage2Pwm );
    motor_B.Rotate( voltage * voltage2Pwm );

}

//temp
    // float speed_L = motor_A.GetSpeed();
    // float speed_R = motor_B.GetSpeed();
    // float psi = GetPsi();
    // String data = String(speed_L) + "," + String(speed_R) + ", " + String(psi);
    //Serial.println(data);
