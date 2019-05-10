// Goal: Update left speed, right speed, psi

void SetupMsTimer2(){
    MsTimer2::set(dt * 1000, TimerInterrupt);
    MsTimer2::start();
}

void TimerInterrupt(){
    sei();

    // system PID controller setting
    float psi = (float)GetPsi();
    motor_A.Update(psi);
    motor_B.Update(psi);

}
