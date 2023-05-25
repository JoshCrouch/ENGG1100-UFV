#ifndef Fluid_h
#define Fluid_h

#include <Arduino.h>
#include <Servo.h>

class Fluid {
    public:
        Fluid(int pumpPin);
        void Begin(int sLiftPin,int tiltPin,int panPin);
        void CommonLoop(int panInput, int tiltInput, int buttons);
        void ResetLift();
        void ResetAim();

    private:
        int _scissorLiftSpeed;
        int _panSpeed;
        int _tiltSpeed;
        int _pumpPin;
        int _tiltPosition;
        int _panPosition;
        int _sLiftDirection;
        int _scissorLiftPosition;
        Servo pan;
        Servo tilt;
        Servo scissorLift;

};

#endif