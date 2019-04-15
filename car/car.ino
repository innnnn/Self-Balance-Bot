# include <I2Cdev.h>
# include <MPU6050.h>
# include <MsTimer2.h>
# include <BalanbotMotor.h>
# include <Wire.h>
# include <Kalman.h>

# include <SoftwareSerial.h>

SoftwareSerial BTSerial(12, 13);

BalanbotMotor motor_A;
BalanbotMotor motor_B;
BalanbotEncoder encoder_A;
BalanbotEncoder encoder_B;

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
}