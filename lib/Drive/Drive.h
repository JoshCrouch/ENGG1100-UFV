#ifndef Drive_h
#define Drive_h
#include <Arduino.h>

struct direction {
  bool direction;
  bool on;
};


class Drive {
    public:
        Drive(int Ren, int Rin1, int Rin2, int Len, int Lin1, int Lin2);
        void CommonLoop(int turn, int buttons);

    private:
        direction _direction;
        float _turn;
        float _turn_factor;

        float _right_speed;
        float _left_speed;

        int _Ren;
        int _Rin1;
        int _Rin2;
        int _Len;
        int _Lin1;
        int _Lin2;
};


#endif