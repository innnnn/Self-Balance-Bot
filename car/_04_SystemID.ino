void StableVoltage_MotorInput(int dir, int voltage){
    // dir: 1->forward, 2->backward
    //voltage mapping: 0~12V -> 0~255
    float output_vol = 255 * (voltage / 12);
    if(dir == 0){
        motor_A.InverseRotationDirectionDefinition(true);
        motor_B.InverseRotationDirectionDefinition(false);
    }else{
        motor_A.InverseRotationDirectionDefinition(false);
        motor_B.InverseRotationDirectionDefinition(true);
    }
    motor_A.rotate(output_vol);
    motor_B.rotate(output_vol);
}