/*
void parseCmd(){
  int commaAt = -1;
  int cmdLen = cmd.length();
  for(int i=0; i<cmdLen; ++i){
    if(cmd[i] == ','){
      commaAt = i;
      break;
    }
  }

  if(commaAt != -1){
    float Power = cmd.substring(0, commaAt).toFloat();
    float Angle = cmd.substring(commaAt+1).toFloat();
    float Sin = sin(Angle * DEG_TO_RAD);
    float Cos = cos(Angle * DEG_TO_RAD);
    float forward = Sin * Sin * (Sin<0?-1.0:1.0);
    float diff = Cos * Cos / 2.0 * (Cos<0?-1.0:1.0) * (forward<0?-1.0:1.0);
    float lRatio = forward + diff;
    float rRatio = forward - diff;

    //give command to wheels
    moveMotor(LEFT, lRatio * Power * maxPowerRemap);
    motor_A.Rotate();
    moveMotor(RIGHT, rRatio * Power * maxPowerRemap);
  }
  cmd = "";
}
*/
