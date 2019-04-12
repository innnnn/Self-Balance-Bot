# include "MsTimer2.h"
# include <SoftwareSerial.h>
SoftwareSerial BTSerial(12, 13); // TX | RX
//left motor
//forward: LEFT_A_PIN-> HIGH, RIGHT_A_PIN-> LOW
# define INT_A_PIN 2
# define DIR_A_PIN A3
# define PWM_A_PIN 5
# define LEFT_A_PIN 6
# define RIGHT_A_PIN 4
//right motor
//forward: LEFT_B_PIN-> LOW, RIGHT_B_PIN-> HIGH
# define INT_B_PIN 3
# define DIR_B_PIN 8
# define PWM_B_PIN 9
# define LEFT_B_PIN 10
# define RIGHT_B_PIN 11

# define STANDBY_PIN 7

const int SECTION_NUMBER = 390;
float dT = 0.01;

//left motor
int count_A = 0;
float currentAngle_A = 0.0;
float lastAngle_A = 0.0;
float speed_A = 0.0;
//right motor
int count_B = 0;
float currentAngle_B = 0.0;
float lastAngle_B = 0.0;
float speed_B = 0.0;

void EncoderInterrupt(){
    if(digitalRead(DIR_A_PIN) == HIGH) ++count_A;
    else if(digitalRead(DIR_A_PIN) == LOW) --count_A;
    else if(digitalRead(DIR_B_PIN) == HIGH) ++count_B;
    else ++count_B;
}

void TimerInterrupt(){
    sei();
    speed_A = (currentAngle_A - lastAngle_A) / dT;
    speed_B = (currentAngle_B - lastAngle_B) / dT;
}

float CalculateAngle(int count){
    return 2 * PI * ((float)count / (float)SECTION_NUMBER) * RAD_TO_DEG;
}

void MotorRotate(int effort_L, int effort_R){
    if(effort_L > 0){
        digitalWrite(LEFT_A_PIN, HIGH);
        digitalWrite(RIGHT_A_PIN, LOW);
    }else{
        digitalWrite(LEFT_A_PIN, LOW);
        digitalWrite(RIGHT_A_PIN, HIGH);
    }
    digitalWrite(STANDBY_PIN, HIGH);
    analogWrite(PWM_A_PIN, effort_L);

    if(effort_R > 0){
        digitalWrite(LEFT_B_PIN, LOW);
        digitalWrite(RIGHT_B_PIN, HIGH);
    }else{
        digitalWrite(LEFT_B_PIN, HIGH);
        digitalWrite(RIGHT_B_PIN, LOW);
    }
    analogWrite(PWM_B_PIN, effort_R);
}

void setup(){
    attachInterrupt(digitalPinToInterrupt(INT_A_PIN), EncoderInterrupt, RISING);
    attachInterrupt(digitalPinToInterrupt(INT_B_PIN), EncoderInterrupt, RISING);
    MsTimer2::set(dT * 1000, TimerInterrupt);
    MsTimer2::start();

    Serial.begin(9600);
    pinMode(PWM_A_PIN, OUTPUT);
    pinMode(LEFT_A_PIN, OUTPUT);
    pinMode(RIGHT_A_PIN, OUTPUT);
    pinMode(PWM_B_PIN, OUTPUT);
    pinMode(LEFT_B_PIN, OUTPUT);
    pinMode(RIGHT_B_PIN, OUTPUT);
    pinMode(STANDBY_PIN, OUTPUT);

    BTSerial.begin(115200);
}

void loop(){
    lastAngle_A = currentAngle_A;
    currentAngle_A = CalculateAngle(count_A);
    Serial.print("Left -> Angle: ");
    Serial.print(currentAngle_A);
    Serial.print(", Speed: ");
    Serial.println(speed_A);

    lastAngle_B = currentAngle_B;
    currentAngle_B = CalculateAngle(count_B);
    Serial.print("Right -> Angle: ");
    Serial.print(currentAngle_B);
    Serial.print(", Speed: ");
    Serial.println(speed_B);

    Serial.println();
    BTSerial.println("123");
}
