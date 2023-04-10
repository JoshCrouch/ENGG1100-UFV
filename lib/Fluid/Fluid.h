#ifndef Fluid_h
#define Fluid_h

#include <Arduino.h>
#include <Servo.h>

class Fluid {
    public:

        Fluid(int nozzlePin, int scissorLiftPin, int pumpPin);
        void CommonLoop(int scissorLiftSpeed, int nozzleAngle, int pumpSpeed);

    private:
        int pumpPin;
        Servo nozzle;
        Servo scissorLift;

};

#endif