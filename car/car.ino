# include <I2Cdev.h>
# include <MPU6050.h>
# include <MsTimer2.h>
# include <BalanbotMotor.h>
# include <Wire.h>
# include <Kalman.h>

# include <SoftwareSerial.h>

SoftwareSerial BTSerial(12, 13);
char val;
String receiveData = "";
bool startReceive = false;

BalanbotMotor motor_A;
BalanbotMotor motor_B;
BalanbotEncoder encoder_A;
BalanbotEncoder encoder_B;

float dT = 0.01;

Kalman kalman; // Create the Kalman instances

/* IMU Data */
double accX, accY, accZ;
double gyro;

double kalAngle; // Calculated angle using a Kalman filter

uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data

int serial_input;

void TimerInterrupt(){
    sei();

    float speed_L = encoder_A.GetSpeed(dT) * (-1);
    float speed_R = encoder_B.GetSpeed(dT);
    double psi = GetPsi();

    Serial.print("speed_left  = ");
    Serial.print(speed_L);
    Serial.print(", speed_right = ");
    Serial.print(speed_R);
    Serial.print(", psi = ");
    Serial.println(psi);

    //BT.println(speed_L);
    //BT.println(speed_R);
    //BT.println(psi);
}

void Encoder_A_Interrupt(){
    encoder_A.Update();
}
void Encoder_B_Interrupt(){
    encoder_B.Update();
}

void setup(){
    Serial.begin(9600);
    BTSerial.begin(115200);
    SetupMotor();
    SetupEncoder();
    SetupMPU6050();

    MsTimer2::set(dT*1000, TimerInterrupt);
    MsTimer2::start();
}

void loop(){
    //updateBT();
    if(Serial.available()){
        serial_input = Serial.read();
        StableVoltage_MotorInput(0, serial_input);
    }
}
