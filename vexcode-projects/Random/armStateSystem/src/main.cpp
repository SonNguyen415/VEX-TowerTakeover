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
// Lift                 motor         19              
// Controller1          controller                    
// Motor                motor         18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

const int IDLE = 0;
const int LOW = 1;
const int MEDIUM = 2;
const int HIGH = 3;

int currentState = IDLE;
int count = 0;
bool buttonPressed = Controller1.ButtonA.pressing();

void readState() {
  buttonPressed = Controller1.ButtonA.pressing();
  count = count + 1;
}

int evaluateState(int currentState) {
  switch(currentState) {
    case IDLE:
      if(buttonPressed && count > 10) {
        return LOW;
      }
      break;
    case LOW:
      if(!buttonPressed && count > 5) {
        return IDLE;
      }
      break;
  }
  return currentState;
}

void reactToState(int currentState) {
  switch(currentState) {
    case IDLE:
      break;
    case LOW:
      Motor.spinFor(50, degrees);
      break;
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  while(1) {
    readState();
    currentState = evaluateState(currentState);
    reactToState(currentState);
  }
}
