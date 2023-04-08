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

//Control
#define dataPin   53    // Brown wire
#define cmdPin    51    // Orange wire
#define attPin    49    // Yellow wire
#define clockPin  47    // Blue wire

//Drive
#define driveEnable 10  //Enable pin for L293D
#define driveIn1 9      //Input 1 for L293D
#define driveIn2 8      //Input 2 for L293D

//Fluid
#define nozzlePin 3     //Pin for the nozzle servo
#define sLiftPin 5      //Pin for the nozzle servo
#define pumpPin 11      //Pin for the pump mos module

// PSX library setup
PSX psx;
PSX::PSXDATA PSXdata;
int PSXerror;

//Setup Servo
Servo nozzleServo;
Servo sLiftServo;
int sLiftPos = 0;
int sLSpeed = 0.5;

void setup() {
  //Setup the PSX library
  psx.setupPins(dataPin, cmdPin, attPin, clockPin, 10);
  psx.config(PSXMODE_ANALOG);

  //Setup drive pins
  pinMode(driveEnable, OUTPUT);
  pinMode(driveIn1, OUTPUT);
  pinMode(driveIn2, OUTPUT);

  //Setup fluid servos and pins
  nozzleServo.attach(nozzlePin);
  sLiftServo.attach(sLiftPin);
  pinMode(pumpPin, OUTPUT);

  // Setup serial communication
  Serial.begin(9600);
}

void DriveLoop() {
  //Read & Map Joystick position for drive
  int JoyStickLeftY = PSXdata.JoyLeftY;
  int driveControl = -1 * map(JoyStickLeftY, 0, 256, -255, 255);

  //PWM write to L293D
  analogWrite(driveEnable, abs(driveControl));
  
  //Change direction based on sign of driveControl
  if(driveControl > 0){
    digitalWrite(driveIn1, LOW);
    digitalWrite(driveIn2, HIGH);
  } else {
    digitalWrite(driveIn1, HIGH);
    digitalWrite(driveIn2, LOW);
  }
}

void FluidLoop() {
  //Read & Map Joystick position for Nozzle
  int JoyStickRightX = PSXdata.JoyRightX;
  int nozzlePos = map(JoyStickRightX, 0, 255, 0, 180);
  nozzleServo.write(nozzlePos);

  //Read & Map Joystick position for Scissor Lift
  int JoyStickRightY = PSXdata.JoyRightY;
  int sLiftControl = map(JoyStickRightY, 0, 255, 0, 180);
  sLiftServo.write(sLiftControl);

  //Read & Map Joystick position for Pump
  int JoyStickLeftX = PSXdata.JoyLeftX;
  int pumpControl = map(JoyStickLeftX, 0, 255, -255, 255);
  analogWrite(pumpPin, abs(pumpControl));
}

void loop() {
  //Read Controller state
  PSXerror = psx.read(PSXdata);

  //Check if the read was successful
  if(PSXerror == PSXERROR_SUCCESS){
    DriveLoop();
    FluidLoop();
  } else {
    Serial.println("No data");
  }
  delay(10);
}

