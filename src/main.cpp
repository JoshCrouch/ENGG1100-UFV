/*
Controls:
  - Left Joystick Y   ->  Drive
  - Left Joystick X   ->  Pump
  - Right Joystick X  ->  Pan
  - Right Joystick Y  ->  Tilt
  - dPad  Vertical    ->  Scissor Lift
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
#define sLiftPin 3       //Pin for the Scissor Lift servo
#define tiltPin 5        //Pin for tilt servo
#define panPin 6         //Pin for pan servo
#define pumpPin 11        //Pin for the pump mos module

// PSX library setup
PSX psx;
PSX::PSXDATA PSXdata;
int PSXerror;

int sLiftControl;
int sLiftSpeed = 1;
int panSpeed = 5;
int tiltSpeed = 5;

Drive driveSystem(driveEnablePin,driveIn1Pin,driveIn2Pin);
Fluid fluidSystem(pumpPin, sLiftSpeed, panSpeed, tiltSpeed);

void setup() {
  //Setup the PSX library
  psx.setupPins(dataPin, cmdPin, attPin, clockPin, 10);
  psx.config(PSXMODE_ANALOG);

  fluidSystem.Begin(sLiftPin,tiltPin,panPin);

  // Setup serial communication
  Serial.begin(9600);
}

void loop() {
  //Read Controller state
  PSXerror = psx.read(PSXdata);

  if(PSXerror == PSXERROR_SUCCESS){
    if (PSXdata.buttons == PSXBTN_UP){sLiftControl = 1;}
    else if(PSXdata.buttons == PSXBTN_DOWN){sLiftControl = -1;}
    else {sLiftControl = 0;}

    if (PSXdata.buttons == PSXBTN_CIRCLE){
      fluidSystem.ResetPositions();
    }

    driveSystem.CommonLoop(PSXdata.JoyLeftY);
    fluidSystem.CommonLoop(PSXdata.JoyRightX, PSXdata.JoyRightY, sLiftControl, PSXdata.JoyLeftX);
  } else {
    Serial.println("No data");
  }
  
  delay(10);
}