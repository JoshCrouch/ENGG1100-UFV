#ifndef Fluid_h
#define Fluid_h

#include <Arduino.h>
#include <Servo.h>

class Fluid {
    public:
        Fluid(int pumpPin, int scissorLiftSpeed, int panSpeed, int tiltSpeed);
        void Begin(int sLiftPin,int tiltPin,int panPin);
        void CommonLoop(int panInput, int tiltInput, int sLiftInput, int pumpSpeed);
        void ResetPositions();

    private:
        int scissorLiftSpeed;
        int panSpeed;
        int tiltSpeed;
        int pumpPin;
        int tiltPosition;
        int panPosition;
        int scissorLiftPosition;
        Servo pan;
        Servo tilt;
        Servo scissorLift;

};

#endif