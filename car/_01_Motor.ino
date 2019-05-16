void SetupMotor(){
/*-- pin setup ------------------------------------------------------------------*/
// If batterys are at backward & user see the car from the backward
// motor A(right motor) connected between A01 and A02
// motor B(left motor) connected between B01 and B02
    const int PWMA = 5, PWMB = 9;               // Speed control 
    const int AIN1 = 6, BIN1 = 11;              // Direction +
    const int AIN2 = 4, BIN2 = 10;              // Direction -
    const int STBY = 7;                         // standby(停止)

    const int INTA = 2, INTB = 3;               // Encoder interrupt
    const int DIRA = A3, DIRB = 8;              // Encoder direction

    // left motor
    motor_A.SetPwmPin(PWMA);
    motor_A.SetDirectionPins(AIN1, AIN2);
    motor_A.SetStandbyPin(STBY);
    motor_A.SetSamplingTime(dt);
    
    motor_A.SetEncoder(-1, INTA, DIRA);
    attachInterrupt(digitalPinToInterrupt(motor_A.GetEncoderInterruptPin()), Encoder_A_Interrupt, RISING);

    motor_A.SetControlMode(1);
    motor_A.SetPsiController(0, 50.0, 30.0, 1.0);
    
    // 70.0, 30.0, 1.0    
    // right motor
    motor_B.SetPwmPin(PWMB);
    motor_B.SetDirectionPins(BIN1, BIN2);
    motor_B.SetStandbyPin(STBY);
    motor_B.SetSamplingTime(dt);
    
    motor_B.SetEncoder(1, INTB, DIRB);
    attachInterrupt(digitalPinToInterrupt(motor_B.GetEncoderInterruptPin()), Encoder_B_Interrupt, RISING);

    motor_B.SetControlMode(1);
    motor_B.SetPsiController(0, 50.0, 30.0, 1.0);
}

void Encoder_A_Interrupt(){
    motor_A.UpdateEncoder();
}

void Encoder_B_Interrupt(){
    motor_B.UpdateEncoder();
}
