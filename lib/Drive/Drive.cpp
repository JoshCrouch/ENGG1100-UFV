/*
  A library to abstract the controls of the drive subsystem in the UFV
*/
#include <Arduino.h>
#include <Drive.h>
#include <PSX.h>

Drive::Drive(int Ren, int Rin1, int Rin2, int Len, int Lin1, int Lin2) { //Constructor 
  _Ren = Ren;
  _Rin1 = Rin1;
  _Rin2 = Rin2;
  _Len = Len;
  _Lin1 = Lin1;
  _Lin2 = Lin2;

  pinMode(_Ren, OUTPUT);
  pinMode(_Rin1, OUTPUT);
  pinMode(_Rin2, OUTPUT);
  pinMode(_Len, OUTPUT);
  pinMode(_Lin1, OUTPUT);
  pinMode(_Lin2, OUTPUT);
}

void Drive::CommonLoop(int turn, int buttons) {
  if (buttons == PSXBTN_R2) {
    _direction.direction = true; //Forward
    _direction.on = true;
  } else if (buttons == PSXBTN_L2) {
    _direction.direction = false; //Backwards
    _direction.on = true;
  } else {
    _direction.on = false;
  }

  _turn = (float)(map((float)turn, 0, 255, -100, 100))/(float)100;
  _turn_factor = 0.5;

  if (_turn > 0) {
    _right_speed = (float)1 - _turn + _turn_factor;
    _left_speed = _turn + _turn_factor;
  } else if (_turn < 0) {
    _left_speed = (float)1 - abs(_turn) + _turn_factor;
    _right_speed = abs(_turn) + _turn_factor;
  } else {
    _left_speed = 1;
    _right_speed = 1;
  }

  if (_direction.on) {
    analogWrite(_Ren, constrain(_right_speed, 0, 1) * 255);
    analogWrite(_Len, constrain(_left_speed, 0, 1) * 255);
  } else {
    analogWrite(_Ren, 0);
    analogWrite(_Len, 0);
  }


  if(_direction.direction){ //Forward
    digitalWrite(_Rin1, HIGH);
    digitalWrite(_Rin2, LOW);
    digitalWrite(_Lin1, HIGH);
    digitalWrite(_Lin2, LOW);
  } else {                  //Backwards
    digitalWrite(_Rin1, LOW);
    digitalWrite(_Rin2, HIGH);
    digitalWrite(_Lin1, LOW);
    digitalWrite(_Lin2, HIGH);
  }
}