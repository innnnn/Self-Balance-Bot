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

float dT = 0.1;

Kalman kalman; // Create the Kalman instances

/* IMU Data */
double accX, accY, accZ;
double gyro;

double kalAngle; // Calculated angle using a Kalman filter

uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data

int serial_input = 0;

void TimerInterrupt(){
    sei();
    float speed_L = encoder_A.GetSpeed(dT) * (-1);
    float speed_R = encoder_B.GetSpeed(dT);
    double psi = GetPsi();
    String data = String(speed_L) + "," + String(speed_R) + "," + String(psi);
//    Serial.println(data);
}

void setup(){
    Serial.begin(9600);
    BTSerial.begin(115200);

    // initialization
    SetupMotor();
    SetupEncoder();
    SetupMPU6050();

    MsTimer2::set(dT*1000, TimerInterrupt);
    MsTimer2::start();
}

void loop(){
   StableVoltage_MotorInput(1, 5);
}
