// Goal: system id need constant 5v input

void StableVoltage(const int voltage){
    motorL.rotate( (int)(voltage) );
    motorR.rotate( (int)(voltage) );
}
