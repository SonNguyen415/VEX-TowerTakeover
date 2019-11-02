/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Sat Nov 02 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// L1                   motor         1               
// L2                   motor         2               
// R1                   motor         3               
// R2                   motor         4               
// A1                   motor         5               
// A2                   motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
motor_group Left(L1, L2); //Group the left wheels into one group
motor_group Right(R1, R2); //Group the right wheels into one group
motor_group Lift(A1, A2); //Group the lift motors into one group

using namespace vex;

double LIFT_SPEED = 50; //Define the lift speed as a constant in percentage

//Set stopping mode for the base to be coast (no active brake)
void setBrakeMode() {
  Left.setStopping(coast);
  Right.setStopping(coast);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  setBrakeMode();

  while (1) {
    //Controller Buttons will spin the lift motors when held
    if(Controller1.ButtonR1.pressing()) {
      Lift.spin(forward, LIFT_SPEED, pct);
    } else if (Controller1.ButtonR2.pressing()) {
      Lift.spin(reverse, LIFT_SPEED, pct);
    } else {
      Lift.stop(hold);
    }

    //The velocity is equated to the joystick position
    double leftVelocity = Controller1.Axis2.position(pct);
    double rightVelocity = Controller1.Axis3.position(pct);    
    Left.spin(forward, leftVelocity, pct);
    Right.spin(forward, rightVelocity, pct);
  }
}
