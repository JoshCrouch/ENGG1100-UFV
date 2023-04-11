#ifndef Fluid_h
#define Fluid_h

#include <Arduino.h>
#include <Servo.h>

class Fluid {
    public:
        Fluid(int pumpPin);
        void Begin(int nozzlePin, int scissorLiftPin);
        void CommonLoop(int scissorLiftSpeed, int nozzleAngle, int pumpSpeed);

    private:
        int pumpPin;
        Servo nozzle;
        Servo scissorLift;

};

#endif