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

// parameter
float psi = 0;

float thetaL;
float thetaR;
float theta;
float speedL;
float speedR;
float Speed;

float phi = 0;
float speedX;
float speedY;

// sampling
unsigned long previousTime;
unsigned long currentTime;
float samplingTime;

unsigned long startTime;
unsigned long gameTime;
unsigned long steadyTime;
unsigned long offsetTime;

// output voltage
float output;
float outputDiff;
float outputR;
float outputL;

float desirePos = 0;
float desirePsi = 0;
float desirePhi = 0;

bool steady = false;
int index = -1;

// 03_Timer
bool startReadData = false;
String rawData = "";
int commaNumber = 0;
int len = 0;
float *data = new float[12];

// game3
bool startTurn = false;
bool startMove = false;

char Move = "A";
char Color = "A";

// game2
double sendPsi;
double sendPhi;
double maxPsi = 0.03;
double maxPhi = 3*PI/4;

// bug!!!!
// abs in arduino: return int
//#define abs(x) ((x)>0?(x):-(x))

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
    psi = ((float)GetPsi())/180*PI;  //rad
    
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

    // game mode
    //Game1();
    //Game2();
    Game2Temp();
    //Game1Temp();
    //Game3();
    
    motorL.rotate( outputL );
    motorR.rotate( outputR );

    // game2
    if( abs(desirePhi)<0.001 ){
        encoderL.reset();
        encoderR.reset();
    }
    
    // record the previous time
    previousTime = currentTime;
}
