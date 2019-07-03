// Goal: Setup motor, encoder, controller

void setupCar(){
/*-- pin setup ------------------------------------------------------------------*/
// If batterys are at backward & user see the car from the backward
// motor A(right motor) connected between A01 and A02
// motor B(left  motor) connected between B01 and B02
    const int PWMA = 5, PWMB = 9;               // Speed control 
    const int AIN1 = 6, BIN1 = 11;              // Direction +
    const int AIN2 = 4, BIN2 = 10;              // Direction -
    const int STBY = 7;                         // standby(停止)

    const int INTA = 2, INTB = 3;               // Encoder interrupt
    const int DIRA = A3, DIRB = 8;              // Encoder direction

    // left motor
    motorL.setPin(PWMA, AIN1, AIN2, STBY);

    // right motor
    motorR.setPin(PWMB, BIN1, BIN2, STBY);

    // left encoder
    encoderL.setMotorSide(-1);
    encoderL.setPin(INTA, DIRA);
    attachInterrupt(digitalPinToInterrupt(encoderL.getInterruptPin()), encoderLInterrupt, RISING);
    
    // right encoder
    encoderR.setMotorSide(1);
    encoderR.setPin(INTB, DIRB);
    attachInterrupt(digitalPinToInterrupt(encoderR.getInterruptPin()), encoderRInterrupt, RISING);

    // psi controller
    psiController.setSaturation(12.0, -12.0);  // 12v ~ -12v
    psiController.setToleratedError(0.02);     // 0.02rad
    psiController.setPID(93.5, 600, 1.1);      // KP, KI, KD
    psiController.setReference(0.0);           // Reference

    // pos controller
    posController.setSaturation(0.02, -0.02);  // 0.02rad ~ -0.02rad
    posController.setToleratedError(W);        // W cm
    posController.setPID(0.001);               // KP  0.001
    posController.setReference(0.0);           // Reference

    // phi controller
    phiController.setSaturation(3, -3);        // 3v ~ -3v
    phiController.setToleratedError(0.0262);   // 0.0262rad -> 1.5degree
    phiController.setPID(100);                 // KP  100
    psiController.setReference(0.0);           // Reference

    // for game 1
    //phiController.setToleratedError(0.0873);   // 0.0873rad -> 5degree
    //phiController.setPID(1);                   // KP  1
}

void encoderLInterrupt(){
    encoderL.updatePPR();
}

void encoderRInterrupt(){
    encoderR.updatePPR();
}
