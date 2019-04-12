#include "BalanbotMotor.h"

/*
BalanbotMotor::BalanbotMotor() :
  mDirectionCoefficient (1.0),
  mSpeed (0.0),
  mAngle (0.0),
  mControlMode (0)
{

}
*/

inline void BalanbotMotor::SetPWMPin(const int pin)
{
  mPwmPin = pin;
  //TODO
  pinMode(mPwmPin, OUTPUT);
}

inline void BalanbotMotor::SetDirectionPins( const int pinA, 
                                             const int pinB )
{
  mDirectionPinA = pinA;
  mDirectionPinB = pinB; 
  //TODO
  pinMode(mDirectionPinA, OUTPUT);
  pinMode(mDirectionPinB, OUTPUT);
}

inline void BalanbotMotor::SetStandbyPin(const int pin)
{
  mStandbyPin = pin;
  //TODO
  pinMode(mStandbyPin, OUTPUT);
}

void BalanbotMotor::SetMotorPins( const int pwmPin, 
                                  const int directionPinA, 
                                  const int directionPinB, 
                                  const int standbyPin )
{
  SetPWMPin(pwmPin);
  SetDirectionPins(directionPinA, directionPinB);
  SetStandbyPin(standbyPin);
}

void BalanbotMotor::SetEncoderPins( const int interruptPin, 
                                    const int directionPin )
{
  mEncoder.SetInterruptPin(interruptPin);
  mEncoder.SetDirectionPin(directionPin); 
}

void BalanbotMotor::SetControl(int mode, float reference)
{
  //TODO
}

void BalanbotMotor::InverseRotationDirectionDefinition(const bool ifInverse){
  if( ifInverse )
    mDirectionCoefficient = -1.0;
  else
    mDirectionCoefficient = 1.0;
}

int BalanbotMotor::GetEncoderInterruptPin() 
{ 
  return mEncoder.GetInterruptPin();
}

float BalanbotMotor::GetSpeed() 
{
  return mSpeed;
} 

float BalanbotMotor::GetAngle() 
{
  return mAngle;
}

void BalanbotMotor::Rotate(const int voltage){
  //TODO
  //motor: 0-> left(A), 1-> right(B)
  //speed: 0 ~ 255
  //direction: 0-> clockwise, 1-> counter-clockwise
  boolean pin1 = LOW;   //initial rotate direction: clockwise
  boolean pin2 = HIGH;
  if(mDirectionCoefficient == 1){
    pin1 = HIGH;
    pin2 = LOW;
  }

  digitalWrite(mStandbyPin, HIGH);
  digitalWrite(mDirectionPinA, pin1);
  digitalWrite(mDirectionPinB, pin2);
  analogWrite(mPwmPin, voltage);

  Serial.println(mPwmPin); 
  Serial.println(voltage); 
  Serial.println(mDirectionPinA); 
  Serial.println(pin1); 
  Serial.println(mDirectionPinB); 
  Serial.println(pin2); 
}

void BalanbotMotor::Brake(){
  //TODO
}

void BalanbotMotor::UpdateAngle(){
  int encoderPosition = mEncoder.GetPosition();
  mAngle =  mDirectionCoefficient 
            * (2*PI) 
            * ( static_cast<float>(encoderPosition) 
              / static_cast<float>(mEncoder.GetPPR()) );
}

void BalanbotMotor::UpdateSpeed(){
  mSpeed = mDifferentiator.differential(mAngle);
}

void BalanbotMotor::UpdateEncoder(){
  mEncoder.Update();
}

void BalanbotMotor::UpdateControl()
{
  //TODO
}

void BalanbotMotor::Update(){
  UpdateAngle();
  UpdateSpeed();
  UpdateControl();
}
