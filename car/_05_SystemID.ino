void StableVoltage_MotorInput(int dir, int voltage){
    // dir: 1->forward, 2->backward
    //voltage mapping: 0~12V -> 0~255
    float output_vol = 255 * (voltage / 12.0);
    if(dir == 0){
        motor_A.InverseRotationDirectionDefinition(true);
        motor_B.InverseRotationDirectionDefinition(true);
    }else{
        motor_A.InverseRotationDirectionDefinition(false);
        motor_B.InverseRotationDirectionDefinition(false);
    }
    Serial.println(output_vol);
    motor_A.Rotate((int)output_vol);
    motor_B.Rotate((int)output_vol);
} 
