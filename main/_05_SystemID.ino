// Goal: system id need constant 5v input

void stableVoltage(const int voltage){
    motorL.rotate( (int)(voltage/12.0*255) );
    motorR.rotate( (int)(voltage/12.0*255) );
}
