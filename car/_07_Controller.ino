// Goal: Select the control mode

void SetController(){
    motor_A.Reset();
    motor_B.Reset();
    
    switch( (int)data[1] ){
        case 0:  // nothing
            motor_A.SetControlMode(0);
            motor_B.SetControlMode(0);
            break;
        case 1:  // psi
            motor_A.SetControlMode(1);
            motor_A.SetPsiController(data[2], data[3], data[4], data[5]);
            motor_B.SetControlMode(1);
            motor_B.SetPsiController(data[2], data[3], data[4], data[5]);
            break;
        case 2:  // psi, theta
            motor_A.SetControlMode(2);
            motor_A.SetPsiController(data[2], data[3], data[4], data[5]);
            motor_A.SetThetaController(data[6], data[7], data[8], data[9]);
            motor_B.SetControlMode(2);
            motor_B.SetPsiController(data[2], data[3], data[4], data[5]);
            motor_B.SetThetaController(data[6], data[7], data[8], data[9]);
            break;
        case 3:  // state feedback
            motor_A.SetControlMode(3);
            motor_A.SetStateFeedbackController(data[2], data[3], data[4], data[5]);
            motor_B.SetControlMode(3);
            motor_B.SetStateFeedbackController(data[2], data[3], data[4], data[5]);
            break;
    }
}
