#ifndef Drive_h
#define Drive_h
#include <Arduino.h>

class Drive {
    public:
        Drive(int enablePin, int in1, int in2);
        void CommonLoop(int speed);

    private:
        int speed;
        bool direction;

        int enablePin;
        int in1;
        int in2;
};


#endif