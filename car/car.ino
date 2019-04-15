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

// sampling time
// max sampling time: 0.025s
// max sampling rate: 40Hz
float dT = 0.05;

Kalman kalman; // Create the Kalman instances

/* IMU Data */
double accX, accY, accZ;
double gyro;

double kalAngle; // Calculated angle using a Kalman filter

uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data

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
    StableVoltage_MotorInput(1, 1);
}