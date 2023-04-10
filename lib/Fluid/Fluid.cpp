#include <Arduino.h>
#include <Fluid.h>
#include <Servo.h>

Fluid::Fluid(int nozzlePin, int scissorLiftPin, int pumpPin){ //Constructor
    this->pumpPin = pumpPin;
    this->nozzle.attach(nozzlePin);
    this->scissorLift.attach(scissorLiftPin);
    pinMode(pumpPin, OUTPUT);

}

void Fluid::CommonLoop(int scissorLiftSpeed, int nozzleAngle, int pumpSpeed) {
    int nozzlePos = map(nozzleAngle, 0, 255, 0, 180);
    this->nozzle.write(nozzlePos);

    int scissorLiftControl = map(scissorLiftSpeed, 0, 255, 0, 180);
    this->scissorLift.write(scissorLiftControl);

    int pumpControl = map(pumpSpeed, 0, 255, -255, 255);
    analogWrite(this->pumpPin, abs(pumpControl));
}