// Goal: Select the control mode

void SetController(){
    motor_A.Reset();
    motor_B.Reset();
    String s = "";
    switch( (int)data[2] ){
        case 0:  // nothing
            motor_A.SetControlMode(0);
            motor_B.SetControlMode(0);
            break;
        case 1:  // psi same
            motor_A.SetControlMode(1);
            motor_A.SetPsiController(data[3], data[4], data[5], data[6]);
            motor_B.SetControlMode(1);
            motor_B.SetPsiController(data[3], data[4], data[5], data[6]);
            s = "~2,1,"
                 + motor_A.GetPsiControllerInformation() + ","
                 + motor_B.GetPsiControllerInformation() + "#";
            BTSerial.println(s);
            break;
        case 2:  // psi different
            motor_A.SetControlMode(1);
            motor_A.SetPsiController(data[3], data[4], data[5], data[6]);
            motor_B.SetControlMode(1);
            motor_B.SetPsiController(data[7], data[8], data[9], data[10]);
            s = "~2,1,"
                 + motor_A.GetPsiControllerInformation() + ","
                 + motor_B.GetPsiControllerInformation() + "#";
            BTSerial.println(s);
            break;
        case 3:  // theta same
            motor_A.SetControlMode(2);
            motor_A.SetThetaController(data[3], data[4], data[5], data[6]);
            motor_B.SetControlMode(2);
            motor_B.SetThetaController(data[3], data[4], data[5], data[6]);
            s = "~2,2,"
                 + motor_A.GetThetaControllerInformation() + ","
                 + motor_B.GetThetaControllerInformation() + "#";
            BTSerial.println(s);
            break;
        case 4:  // theta different
            motor_A.SetControlMode(2);
            motor_A.SetThetaController(data[3], data[4], data[5], data[6]);
            motor_B.SetControlMode(2);
            motor_B.SetThetaController(data[7], data[8], data[9], data[10]);
            s = "~2,2,"
                 + motor_A.GetThetaControllerInformation() + ","
                 + motor_B.GetThetaControllerInformation() + "#";
            BTSerial.println(s);
        case 5:  // state feedback
            motor_A.SetControlMode(3);
            motor_A.SetStateFeedbackController(data[3], data[4], data[5], data[6]);
            motor_B.SetControlMode(3);
            motor_B.SetStateFeedbackController(data[3], data[4], data[5], data[6]);
            break;
    }
}
