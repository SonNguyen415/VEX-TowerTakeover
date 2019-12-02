/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Tue Nov 12 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Left                 motor         20              
// Right                motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>
#include <string>
using namespace vex;

const int IDLE = 0;
const int BELOW_SETPOINT = 1;
const int ABOVE_SETPOINT = 2;

int currentState = IDLE;

const double kP = 0.5;
const double setPoint = 500;

double leftRotation;
double rightRotation;
double error;
double motorVelocity;

void readState() {
  leftRotation = Left.rotation(rotationUnits::deg);
  rightRotation = Right.rotation(rotationUnits::deg); 

  error =  setPoint - (leftRotation + rightRotation) / 2;
  motorVelocity = error * kP; 

}

int evaluateState(int myState) {
  switch(myState) {
    case IDLE:
      break;
    case BELOW_SETPOINT: 
      break;
    case ABOVE_SETPOINT:
      break;
  }
  return myState;
}

void reactToState(int myState) {
  switch(myState) {
    case IDLE:
      break;
    case BELOW_SETPOINT: 
      break;
    case ABOVE_SETPOINT:
      break;
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(1) {
    readState();
    currentState= evaluateState(currentState);
    reactToState(currentState);
    Brain.Screen.print(motorVelocity);
  }
}

