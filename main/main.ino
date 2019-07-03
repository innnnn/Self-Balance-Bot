# include <Motor.h>
# include <Encoder.h>
# include <PosController.h>
# include <PsiController.h>
# include <PhiController.h>

# include <I2Cdev.h>
# include <MPU6050.h>
# include <MsTimer2.h>

# include <Wire.h>
# include <Kalman.h>
# include <SoftwareSerial.h>

// constant
const float R = 3.3;
const float W = 18.7;

// Bluetooth
SoftwareSerial BTSerial(12, 13);    //tx, rx

// motor
Motor motorL;
Motor motorR;

// encoder
Encoder encoderL;
Encoder encoderR;

// controller
PosController posController;
PsiController psiController;
PhiController phiController;

// main parameter
float psi = 0;

// sampling
unsigned long previousTime;
unsigned long currentTime;
float samplingTime;

// angle and speed
float thetaL;
float thetaR;
float theta;
float speedL;
float speedR;
float Speed;

float phi = 0;
float speedX;
float speedY;

// output voltage
float output;
float outputDiff;
float outputR;
float outputL;

// 03_Timer
bool startReadData = false;
String rawData = "";
int len = 0;
float *data = new float[12];

// game1
unsigned long startTime;
unsigned long gameTime;
float steadyTime;
unsigned long offsetTime;
bool steady = false;
int index = -1;

// game2
float desirePos = 0;
float desirePsi = 0;
float desirePhi = 0;

// game3
bool startTurn = false;
bool startMove = false;
char Move = "A";
char Color = "A";


void setup(){
    Serial.begin(9600);
    BTSerial.begin(57600);
    
    // initialize car, MPU6050, MsTimer2
    setupCar();
    setupMPU6050();
    setupMsTimer2();
    
    // initialize the previous time
    previousTime = millis();
    startTime = previousTime;
}

// update controller
void loop(){
    // compute the sampling time
    currentTime = millis();
    samplingTime = (currentTime - previousTime)/1000.0;

    // in case for samplingTime = 0
    if( samplingTime < 0.001 )
        samplingTime = 0.001;

    // update the current state
    psi = ((float)getPsi())/180*PI;  //rad
    
    encoderL.update(samplingTime);
    encoderR.update(samplingTime);
    thetaL = encoderL.getAngle();
    thetaR = encoderR.getAngle();
    theta = R*(thetaL + thetaR)/2;
    
    speedL = encoderL.getSpeed();
    speedR = encoderR.getSpeed();
    Speed = R*(speedL + speedR)/2;
    
    phi = R*(thetaL - thetaR)/W;
    speedX = R*(speedL + speedR)*sin(phi)/2;
    speedY = -R*(speedL + speedR)*cos(phi)/2;
    
    // check the car is balancing or not
    if( fabs(psi)<PI/4 ){  
        // game mode
        game1();
        //game2();
        //game3();
    } else { // the car is falling down
        outputL = 0;
        outputR = 0;
    }
    
    // move the car
    motorL.rotate( outputL );
    motorR.rotate( outputR );

    // record the previous time
    previousTime = currentTime;
}
