# include <I2Cdev.h>
# include <MPU6050.h>
# include <MsTimer2.h>
# include <BalancebotMotor.h>
# include <Wire.h>
# include <Kalman.h>
# include <SoftwareSerial.h>
SoftwareSerial BTSerial(12, 13);    //tx, rx

// sampling time
// max sampling time: 0.025s
// max sampling rate: 40Hz
// sampling time: 0.05s
// sampling rate: 20Hz
const float dt 0.05

// create new objects(motors)
BalanbotMotor motor_A;
BalanbotMotor motor_B;

// voltage to pwm
const  voltage2Pwm = 255/12.0;

void setup(){
    Serial.begin(9600);
    BTSerial.begin(115200);

    // initialization
    SetupMotor();
    SetupEncoder();
    SetupMPU6050();
    SetupMsTimer2();
}

void loop(){
    //UpdateSerial();
    //UpdateBlueTooth();
    StableVoltage(5);
}
