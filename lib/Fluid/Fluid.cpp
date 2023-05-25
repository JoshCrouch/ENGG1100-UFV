#include <Arduino.h>
#include <Fluid.h>
#include <Servo.h>
#include <PSX.h>

Fluid::Fluid(int pumpPin){ //Constructor
    _panSpeed = -2;
    _tiltSpeed = 1;
    _pumpPin = pumpPin;
    _tiltPosition = 90;
    _panPosition = 90;
    _scissorLiftPosition = 0;
    pinMode(pumpPin, OUTPUT);
}

void Fluid::Begin(int sLiftPin,int tiltPin,int panPin) {
    scissorLift.attach(sLiftPin);
    tilt.attach(tiltPin);
    pan.attach(panPin);
}

void Fluid::CommonLoop(int panInput, int tiltInput, int buttons) {
    //Pan & Tilt
    int pan_update = map(panInput, 0, 255, -1, 1);
    _panPosition += pan_update * _panSpeed;
    _panPosition = constrain(_panPosition, 0, 180);
    pan.write(_panPosition);

    int tilt_update = map(tiltInput, 0, 255, -1, 1);
    _tiltPosition += tilt_update * _tiltSpeed;
    _tiltPosition = constrain(_tiltPosition, 0, 180);
    tilt.write(_tiltPosition);

    if (buttons == PSXBTN_UP) {
        _sLiftDirection = 1; //Forward
    } else if (buttons == PSXBTN_DOWN) {
        _sLiftDirection = -1; //Backwards
    } else {
        _sLiftDirection = 0; //Don't move
    }

    //Scissor Lift
    _scissorLiftPosition += _sLiftDirection;
    _scissorLiftPosition = constrain(_scissorLiftPosition, 0, 180);
    scissorLift.write(_scissorLiftPosition);

    //Pump
    if (buttons == PSXBTN_CROSS) {
        digitalWrite(_pumpPin, HIGH);
    } else {
        digitalWrite(_pumpPin, LOW);
    }

    //Check Resets
    if (buttons == PSXBTN_CIRCLE) {this->ResetAim();}
    if (buttons == PSXBTN_SQUARE) {this->ResetLift();}
}

void Fluid::ResetLift(){
    _scissorLiftPosition = 0;
    scissorLift.write(_scissorLiftPosition);
}

void Fluid::ResetAim(){
    _panPosition = 90;
    _tiltPosition = 90;
    pan.write(_panPosition);
    tilt.write(_tiltPosition);
}