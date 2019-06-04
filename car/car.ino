# include <I2Cdev.h>
# include <MPU6050.h>
# include <MsTimer2.h>
# include <BalanceBotMotor.h>
# include <Wire.h>
# include <Kalman.h>
# include <SoftwareSerial.h>
SoftwareSerial BTSerial(12, 13);    //tx, rx

// create new objects(motors)
BalanceBotMotor motor_A;
BalanceBotMotor motor_B;

// sampling
unsigned long previousTime;
unsigned long currentTime;
float samplingTime;

// controll
boolean onControl = true;
float psi;

void setup(){
    Serial.begin(9600);
    BTSerial.begin(57600);

    // initialization
    SetupMotor();
    SetupMPU6050();
    SetupMsTimer();

    // initialize the previous time
    previousTime = millis();
}

// update controller
void loop(){
    if(onControl){
        psi = ((float)GetPsi())/180*PI;

        // compute the sampling time
        currentTime = millis();
        samplingTime = (currentTime - previousTime)/1000.0;

        // update controller
        motor_A.Update(psi, samplingTime);
        motor_B.Update(psi, samplingTime);

        // record the previous time
        previousTime = currentTime;
    }
}
