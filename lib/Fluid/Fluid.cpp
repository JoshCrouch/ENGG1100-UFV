#include <Arduino.h>
#include <Fluid.h>
#include <Servo.h>

Fluid::Fluid(int pumpPin){ //Constructor
    this->pumpPin = pumpPin;
    pinMode(pumpPin, OUTPUT);
}

void Fluid::Begin(int nozzlePin, int scissorLiftPin) {
    nozzle.attach(nozzlePin);
    scissorLift.attach(scissorLiftPin);
}

void Fluid::CommonLoop(int scissorLiftSpeed, int nozzleAngle, int pumpSpeed) {
    int nozzlePos = map(nozzleAngle, 0, 255, 0, 180);
    nozzle.write(nozzlePos);

    int scissorLiftControl = map(scissorLiftSpeed, 0, 255, 0, 180);
    scissorLift.write(scissorLiftControl);

    int pumpControl = map(pumpSpeed, 0, 255, -255, 255);
    analogWrite(this->pumpPin, abs(pumpControl));
}