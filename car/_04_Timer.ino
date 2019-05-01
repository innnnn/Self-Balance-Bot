// Goal: Update left speed, right speed, psi

void SetupMsTimer2(){
    MsTimer2::set(dT * 1000, TimerInterrupt);
    MsTimer2::start();
}

void TimerInterrupt(){
    sei();
    float speed_L = motor_A.GetSpeed() * (-1);
    float speed_R = motor_B.GetSpeed();
    double psi = GetPsi();
    String data = String(speed_L) + "," + String(speed_R) + ", " + String(psi);
    Serial.println(data);
}
