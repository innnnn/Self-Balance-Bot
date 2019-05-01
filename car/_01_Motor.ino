void SetupMotor(){
/*-- pin setup ------------------------------------------------------------------*/
// If batterys are at backward & user see the car from the backward
// motor A(right motor) connected between A01 and A02
// motor B(left motor) connected between B01 and B02
    const int PWMA = 5, PWMB = 9;               // Speed control 
    const int AIN1 = 6, BIN1 = 11;              // Direction +
    const int AIN2 = 4, BIN2 = 10;              // Direction -
    const int STBY = 7;                         // standby(停止)

    // left motor
    motor_A.SetPwmPin(PWMA);
    motor_A.SetDirectionPins(AIN1, AIN2);
    motor_A.SetStandbyPin(STBY);
    

    // right motor
    motor_B.SetPwmPin(PWMB);
    motor_B.SetDirectionPins(BIN1, BIN2);
    motor_B.SetStandbyPin(STBY);
    
}

// left motor movement
// move forward: need to inverse ==> true
// move backward: does not inverse ==> false
void LeftMotorMove(const int pwm){
    if(pwm > 0){
        motor_A.InverseRotationDirectionDefinition(true);
        motor_A.Rotate(pwm);
    }
    else{
        motor_A.InverseRotationDirectionDefinition(false);
        motor_A.Rotate(-pwm);
    }
}

// right motor movement
// move forward: does not inverse ==> false
// move backward: need to inverse ==> true
void RightMotorMove(const int pwm){
    if(pwm > 0){
        motor_B.InverseRotationDirectionDefinition(false);
        motor_B.Rotate(pwm);
    }
    else{
        motor_B.InverseRotationDirectionDefinition(true);
        motor_B.Rotate(-pwm);
    }
}
