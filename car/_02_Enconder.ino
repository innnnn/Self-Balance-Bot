void SetupEncoder(){
    const int INTA = 2, INTB = 3;               // Encoder interrupt
    const int DIRA = A3, DIRB = 8;              // Encoder direction

    // setup left motor encoder
    motor_A.SetEncoder(-1, INTA, DIRA);
    
    // setup right motor encoder
    motor_B.SetEncoder(1, INTB, DIRB);

    attachInterrupt(digitalPinToInterrupt(motor_A.GetEncoderInterruptPin()), Encoder_A_Interrupt, RISING);
    attachInterrupt(digitalPinToInterrupt(motor_B.GetEncoderInterruptPin()), Encoder_B_Interrupt, RISING);
}

void Encoder_A_Interrupt(){
    motor_A.UpdateEncoder();
}

void Encoder_B_Interrupt(){
    motor_B.UpdateEncoder();
}
