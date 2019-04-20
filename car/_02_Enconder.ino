void SetupEncoder(){

    const int INTA = 2, INTB = 3;               // Encoder interrupt
    const int DIRA = A3, DIRB = 8;              // Encoder direction

    motor_A.SetEncoderPins(INTA, DIRA);
    motor_B.SetEncoderPins(INTB, DIRB);
    
    motor_A.SetSamplingTime(0.05);
    motor_B.SetSamplingTime(0.05);

    attachInterrupt(digitalPinToInterrupt(motor_A.GetEncoderInterruptPin()), Encoder_A_Interrupt, RISING);
    attachInterrupt(digitalPinToInterrupt(motor_B.GetEncoderInterruptPin()), Encoder_B_Interrupt, RISING);
}

void Encoder_A_Interrupt(){
    motor_A.UpdateEncoder();
}

void Encoder_B_Interrupt(){
    motor_B.UpdateEncoder();
}
