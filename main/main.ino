# include <I2Cdev.h>
# include <MPU6050.h>
# include <MsTimer2.h>
# include <BalanceBotMotor.h>
# include <BalanceBotEncoder.h>
# include <BalanceBotController.h>
# include <Wire.h>
# include <Kalman.h>
# include <SoftwareSerial.h>

// constant
const float R = 3.25;
const float W = 18.7;

// Bluetooth
SoftwareSerial BTSerial(12, 13);    //tx, rx

// motor
BalanceBotMotor motorA;
BalanceBotMotor motorB;

// encoder
BalanceBotEncoder encoderA;
BalanceBotEncoder encoderB;

// controller
BalanceBotController psiController;
BalanceBotController posController;

// parameter
float psi;
float thetaL;
float thetaR;
float phi;
float x;
float y;

// sampling
unsigned long previousTime;
unsigned long currentTime;
float samplingTime;
float output;
float output_psi;
float output_pos;

void setup(){
    Serial.begin(9600);
    BTSerial.begin(57600);

    // initialization
    SetupCar();
    SetupMPU6050();
    SetupMsTimer();

    // initialize the previous time
    previousTime = millis();
}

// update controller
void loop(){
    // compute the sampling time
    currentTime = millis();
    samplingTime = (currentTime - previousTime)/1000.0;

    // update current state
    psi = ((float)GetPsi())/180*PI;
    encoderA.Update(samplingTime);
    encoderB.Update(samplingTime);
    thetaL = encoderA.GetAngle();
    thetaR = encoderB.GetAngle();
    phi = R/W*(thetaL - thetaR);
    x = R*(thetaL + thetaR)*sin(phi)/2;
    y = -R*(thetaL + thetaR)*cos(phi)/2;


    // update controller
    /*
    output_psi = -psiController.Update(psi, samplingTime);
    if( abs(psi)<0.025 && !posController.isSteady() ){
        output = output_psi;
    }
    else{
       output = -psiController.Update(psi, samplingTime);
    }*/
    //output = -psiController.Update(psi, samplingTime);
    
    float desire_psi = posController.Update(y, samplingTime);
    //Serial.println(desire_psi);
    psiController.SetReference(desire_psi);
    output = -psiController.Update(psi, samplingTime);
    
    motorA.Rotate( output );
    motorB.Rotate( output );
    
    // record the previous time
    previousTime = currentTime;
}

      /* 
      desire_psi = thetaController.Update(angle, samplingTime);
      psiController.SetReference(desire_psi);
      output = -psiController.Update(psi, samplingTime);
      */
      
      /* parallel
      output_psi = -psiController.Update(psi, samplingTime);
      //Serial.println(output_psi);
      output_theta = -thetaController.Update(angle, samplingTime);
      //Serial.println(output_theta);
      output = 0.5 * output_psi + 0.5 * output_theta;
      */
      
      /*
      if( abs(psi)<0.02 && !thetaController.isSteady() )
        output = thetaController.Update(angle, samplingTime);
      else
        output = -psiController.Update(psi, samplingTime);
      */
      
      /*
      if( abs(psi)<0.02 && !thetaController.isSteady() ){
        desire_psi = thetaController.Update(angle, samplingTime);
      }
      else{
        desire_psi = 0;
      }
      psiController.SetReference(desire_psi);
      output = -psiController.Update(psi, samplingTime);
      */
