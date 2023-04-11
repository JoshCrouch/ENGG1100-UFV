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

void Drive::CommonLoop(int speed) {
  this->speed = map(speed, 0, 256, -255, 255);
  this->direction = (speed > 0)? true: false; //Forward = true, Backward = false

  analogWrite(this->enablePin, abs(this->speed));

  if(this->direction){
    digitalWrite(this->in1, LOW);
    digitalWrite(this->in2, HIGH);
  } else {
    digitalWrite(this->in1, HIGH);
    digitalWrite(this->in2, LOW);
  }
}