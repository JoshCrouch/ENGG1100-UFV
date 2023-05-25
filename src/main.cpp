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
#define dataPin   24      // Yellow wire
#define cmdPin    22      // Green wire
#define attPin    26      // Blue wire
#define clockPin  28      // Purple wire

//Drive
#define Ren 10            //Enable pin for L293D
#define Rin1 9            //Input 1 for L293D
#define Rin2 8            //Input 2 for L293D
#define Len 11            //Enable pin for L293D
#define Lin1 12           //Input 1 for L293D
#define Lin2 13           //Input 2 for L293D

//Fluid
#define sLiftPin 3        //Pin for the Scissor Lift servo
#define tiltPin 5         //Pin for tilt servo
#define panPin 6          //Pin for pan servo
#define pumpPin 2         //Pin for the pump mos module

//Extras ;)
#define tonePin 4         //Pin for the speaker

// PSX library setup
PSX psx;
PSX::PSXDATA PSXdata;
int PSXerror;

Drive driveSystem(Ren,Rin1,Rin2,Len,Lin1,Lin2);
Fluid fluidSystem(pumpPin);

void setup() {
  //Setup the PSX library
  psx.setupPins(dataPin, cmdPin, attPin, clockPin, 10);
  psx.config(PSXMODE_ANALOG);

  fluidSystem.Begin(sLiftPin,tiltPin,panPin);

  // Setup serial communication
  Serial.begin(9600);
}

void midi() {

    tone(tonePin, 349, 821.25);
    delay(912.5);
    delay(4.16666666667);
    tone(tonePin, 329, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 349, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 329, 408.75);
    delay(454.166666667);
    delay(4.16666666667);
    tone(tonePin, 261, 615.0);
    delay(683.333333333);
    delay(4.16666666667);
    tone(tonePin, 220, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 293, 408.75);
    delay(454.166666667);
    delay(4.16666666667);
    tone(tonePin, 220, 821.25);
    delay(912.5);
    delay(8.33333333333);
    tone(tonePin, 233, 615.0);
    delay(683.333333333);
    delay(4.16666666667);
    tone(tonePin, 261, 408.75);
    delay(454.166666667);
    delay(4.16666666667);
    tone(tonePin, 261, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 349, 821.25);
    delay(912.5);
    delay(4.16666666667);
    tone(tonePin, 391, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 440, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 523, 408.75);
    delay(454.166666667);
    delay(4.16666666667);
    tone(tonePin, 440, 408.75);
    delay(454.166666667);
    delay(8.33333333333);
    tone(tonePin, 293, 18.75);
    delay(20.8333333333);
    delay(8.33333333333);
    tone(tonePin, 329, 198.75);
    delay(220.833333333);
    delay(8.33333333333);
    tone(tonePin, 293, 821.25);
    delay(912.5);
    delay(4.16666666667);
    tone(tonePin, 220, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 195, 26.25);
    delay(29.1666666667);
    delay(4.16666666667);
    tone(tonePin, 184, 821.25);
    delay(912.5);
    delay(4.16666666667);
    tone(tonePin, 220, 408.75);
    delay(454.166666667);
    delay(4.16666666667);
    tone(tonePin, 293, 615.0);
    delay(683.333333333);
    delay(8.33333333333);
    tone(tonePin, 261, 405.0);
    delay(450.0);
    delay(8.33333333333);
    tone(tonePin, 293, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 261, 615.0);
    delay(683.333333333);
    delay(4.16666666667);
    tone(tonePin, 233, 615.0);
    delay(683.333333333);
    delay(4.16666666667);
    tone(tonePin, 466, 615.0);
    delay(683.333333333);
    delay(4.16666666667);
    tone(tonePin, 440, 408.75);
    delay(454.166666667);
    delay(4.16666666667);
    tone(tonePin, 466, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 440, 615.0);
    delay(683.333333333);
    delay(8.33333333333);
    tone(tonePin, 391, 615.0);
    delay(683.333333333);
    delay(4.16666666667);
    tone(tonePin, 440, 615.0);
    delay(683.333333333);
    delay(4.16666666667);
    tone(tonePin, 349, 408.75);
    delay(454.166666667);
    delay(4.16666666667);
    tone(tonePin, 466, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 440, 615.0);
    delay(683.333333333);
    delay(4.16666666667);
    tone(tonePin, 349, 408.75);
    delay(454.166666667);
    delay(4.16666666667);
    tone(tonePin, 466, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 415, 615.0);
    delay(683.333333333);
    delay(8.33333333333);
    tone(tonePin, 349, 408.75);
    delay(454.166666667);
    delay(4.16666666667);
    tone(tonePin, 466, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 415, 615.0);
    delay(683.333333333);
    delay(4.16666666667);
    tone(tonePin, 349, 615.0);
    delay(683.333333333);
    delay(920.833333333);
    tone(tonePin, 311, 202.5);
    delay(225.0);
    delay(4.16666666667);
    tone(tonePin, 261, 202.5);
    delay(225.0);
    delay(8.33333333333);
    tone(tonePin, 349, 3708.75);
    delay(4120.83333333);

}

void loop() {
  //Read Controller state
  PSXerror = psx.read(PSXdata);

  if(PSXerror == PSXERROR_SUCCESS){
    driveSystem.CommonLoop(PSXdata.JoyLeftX, PSXdata.buttons);
    fluidSystem.CommonLoop(PSXdata.JoyRightX, PSXdata.JoyRightY, PSXdata.buttons);

    if(PSXdata.buttons == PSXBTN_TRIANGLE){
      midi();
    }
  } else {
    Serial.println("No data");
  }
  
  delay(10);
}

