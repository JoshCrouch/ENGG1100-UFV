#include <Arduino.h>
#include <Fluid.h>
#include <Servo.h>

Fluid::Fluid(int pumpPin, int scissorLiftSpeed, int panSpeed, int tiltSpeed){ //Constructor
    this->scissorLiftSpeed = scissorLiftSpeed;
    this->panSpeed = panSpeed;
    this->tiltSpeed = tiltSpeed;
    this->pumpPin = pumpPin;
    this->tiltPosition = 90;
    this->panPosition = 90;
    this->scissorLiftPosition = 90;
    pinMode(pumpPin, OUTPUT);
}

void Fluid::Begin(int sLiftPin,int tiltPin,int panPin) {
    scissorLift.attach(sLiftPin);
    tilt.attach(tiltPin);
    pan.attach(panPin);
}

void Fluid::CommonLoop(int panInput, int tiltInput, int sLiftInput, int pumpSpeed) {
    //Pan & Tilt
    int pan_update = map(panInput, 0, 255, -1, 1);
    this->panPosition += pan_update * this->panSpeed;
    this->panPosition = constrain(this->panPosition, 0, 180);
    pan.write(this->panPosition);

    int tilt_update = map(tiltInput, 0, 255, -1, 1);
    this->tiltPosition += tilt_update * this->tiltSpeed;
    this->tiltPosition = constrain(this->tiltPosition, 0, 180);
    tilt.write(this->tiltPosition);
    Serial.println(this->panPosition, this->tiltPosition);

    //Scissor Lift
    this->scissorLiftPosition += sLiftInput * this->scissorLiftSpeed;
    this->scissorLiftPosition = constrain(this->scissorLiftPosition, 0, 180);
    scissorLift.write(this->scissorLiftPosition);

    //Pump
    int pumpControl = map(pumpSpeed, 0, 255, -255, 255);
    analogWrite(this->pumpPin, abs(pumpControl));
}

void Fluid::ResetPositions(){
    this->scissorLiftPosition = 90;
    this->panPosition = 90;
    this->tiltPosition = 90;
    scissorLift.write(this->scissorLiftPosition);
    pan.write(this->panPosition);
    tilt.write(this->tiltPosition);
}