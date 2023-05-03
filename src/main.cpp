/*
Controls:
  - Left Joystick Y   ->  Drive
  - Left Joystick X   ->  Pump
  - Right Joystick Y  ->  Scissor Lift
  - Right Joystick X  ->  Nozzle
*/

#include <Arduino.h>
#include <PSX.h>
#include <Servo.h>
#include <Drive.h>
#include <Fluid.h>

//Control
#define dataPin   53      // Yellow wire
#define cmdPin    51      // Green wire
#define attPin    49      // Blue wire
#define clockPin  47      // Purple wire

//Drive
#define driveEnablePin 10 //Enable pin for L293D
#define driveIn1Pin 9     //Input 1 for L293D
#define driveIn2Pin 8     //Input 2 for L293D

//Fluid
#define nozzlePin 3       //Pin for the nozzle servo
#define sLiftPin 5        //Pin for the nozzle servo
#define pumpPin 11        //Pin for the pump mos module

// PSX library setup
PSX psx;
PSX::PSXDATA PSXdata;
int PSXerror;

Drive driveSystem(driveEnablePin,driveIn1Pin,driveIn2Pin);
Fluid fluidSystem(pumpPin);

void setup() {
  //Setup the PSX library
  psx.setupPins(dataPin, cmdPin, attPin, clockPin, 10);
  psx.config(PSXMODE_ANALOG);

  fluidSystem.Begin(nozzlePin,sLiftPin);

  // Setup serial communication
  Serial.begin(9600);
}

void loop() {
  //Read Controller state
  PSXerror = psx.read(PSXdata);

  if(PSXerror == PSXERROR_SUCCESS){
    driveSystem.CommonLoop(PSXdata.JoyLeftY);
    fluidSystem.CommonLoop(PSXdata.JoyRightY, PSXdata.JoyRightX, PSXdata.JoyLeftX);
  } else {
    Serial.println("No data");
  }
  
  delay(10);
}