void SetupEncoder(){
    const int INTA = 2, INTB = 3;
    const int DIRA = A3, DIRB = 8;

    encoder_A.SetInterruptPin(INTA);
    encoder_B.SetInterruptPin(INTB);
    encoder_A.SetDirectionPin(DIRA);
    encoder_B.SetDirectionPin(DIRB);

    attachInterrupt(digitalPinToInterrupt(encoder_A.GetInterruptPin()), Encoder_A_Interrupt, RISING);
    attachInterrupt(digitalPinToInterrupt(encoder_B.GetInterruptPin()), Encoder_B_Interrupt, RISING);
}

void Encoder_A_Interrupt(){
    encoder_A.Update();
}

void Encoder_B_Interrupt(){
    encoder_B.Update();
}
