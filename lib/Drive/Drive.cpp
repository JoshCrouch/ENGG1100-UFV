/*
  A library to abstract the controls of the drive subsystem in the UFV
*/
#include <Arduino.h>
#include <Drive.h>

Drive::Drive(int enablePin, int in1, int in2) { //Constructor 
  this->enablePin = enablePin;
  this->in1 = in1;
  this->in2 = in2;

  pinMode(this->enablePin, OUTPUT);
  pinMode(this->in1, OUTPUT);
  pinMode(this->in2, OUTPUT);
}

<<<<<<< Updated upstream
void Drive::CommonLoop(int speed) {
  this->speed = map(speed, 0, 256, -255, 255);
  this->direction = (this->speed > 0) ? true: false; //Forward = true, Backward = false
=======
void Drive::CommonLoop(int turn, int buttons) {
  if (buttons == PSXBTN_R2) {
    _direction.on = true;
  } else if (buttons == PSXBTN_L2) {
    _direction.on = true;
  } else {
    _direction.on = false;
  }
>>>>>>> Stashed changes

  analogWrite(this->enablePin, abs(this->speed));

<<<<<<< Updated upstream
  if(this->direction){ //Forward
    digitalWrite(this->in1, LOW);
    digitalWrite(this->in2, HIGH);
  } else {                  //Backwards
    digitalWrite(this->in1, HIGH);
    digitalWrite(this->in2, LOW);
=======
  // if (_turn > 0) {
  //   _right_speed = (float)1 - _turn + _turn_factor;
  //   _left_speed = _turn + _turn_factor;
  // } else if (_turn < 0) {
  //   _left_speed = (float)1 - abs(_turn) + _turn_factor;
  //   _right_speed = abs(_turn) + _turn_factor;
  // } else {
  //   _left_speed = 1;
  //   _right_speed = 1;
  // }

  if (_turn > 0) {
    _direction.r_direction = true;
    _direction.l_direction = false;
  } else if (_turn < 0) {
    _direction.r_direction = false;
    _direction.l_direction = true;
  } else {
    _direction.l_direction = true;
    _direction.r_direction = true;
  }

  if (buttons == PSXBTN_R2) {
    _direction.on = true;
  } else if (buttons == PSXBTN_L2) {
    _direction.on = true;
    _direction.l_direction = !_direction.l_direction;
    _direction.r_direction = !_direction.r_direction;
  } else {
    _direction.on = false;
  }

  if (_direction.on) {
    analogWrite(_Ren, 255);
    analogWrite(_Len, 255);
  } else {
    analogWrite(_Ren, 0);
    analogWrite(_Len, 0);
  }

  if(_direction.l_direction){
    digitalWrite(_Lin1, HIGH);
    digitalWrite(_Lin2, LOW);
  } else  {
    digitalWrite(_Lin1, LOW);
    digitalWrite(_Lin2, HIGH);
>>>>>>> Stashed changes
  }

  if(_direction.r_direction){
    digitalWrite(_Rin1, HIGH);
    digitalWrite(_Rin2, LOW);
  } else  {
    digitalWrite(_Rin1, LOW);
    digitalWrite(_Rin2, HIGH);
  }

  // if(_direction.direction){ //Forward
  //   digitalWrite(_Rin1, HIGH);
  //   digitalWrite(_Rin2, LOW);
  //   digitalWrite(_Lin1, HIGH);
  //   digitalWrite(_Lin2, LOW);
  // } else {                  //Backwards
  //   digitalWrite(_Rin1, LOW);
  //   digitalWrite(_Rin2, HIGH);
  //   digitalWrite(_Lin1, LOW);
  //   digitalWrite(_Lin2, HIGH);
  // }
}