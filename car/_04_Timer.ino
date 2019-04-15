// Goal: Get left speed, right speed, psi

// sampling time
// max sampling time: 0.025s
// max sampling rate: 40Hz
// sampling time: 0.05
// sampling rate: 20Hz
float dT = 0.05;

void SetupMsTimer2(){
    MsTimer2::set(dT*1000, TimerInterrupt);
    MsTimer2::start();
}

void TimerInterrupt(){
    sei();
    float speed_L = encoder_A.GetSpeed(dT) * (-1);
    float speed_R = encoder_B.GetSpeed(dT);
    double psi = GetPsi();
    String data = String(speed_L) + "," + String(speed_R) + ", " + String(psi);
}