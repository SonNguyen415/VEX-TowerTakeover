/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Sat Nov 09 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intake1              motor         2               
// Intake2              motor         3               
// R1                   motor         4               
// R2                   motor         5               
// L1                   motor         11              
// L2                   motor         12              
// Lift                 motor         1               
// Tilter               motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

motor_group Left(L1, L2);
motor_group Right(R1, R2);
motor_group Intake(Intake1, Intake2);
using namespace vex;

float MAX_TILT_ROTATION = 300;
float MAX_LIFT_ROTATION = 1000;

void resetAllRotation() {
  Left.resetRotation();
  Right.resetRotation();
  Lift.resetRotation();
  Intake.resetRotation();
  Tilter.resetRotation();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  resetAllRotation();

  if (Controller1.ButtonR1.pressing()) {
    Intake.spin(forward, 100, percent); 
  } else if (Controller1.ButtonR2.pressing()) {
    Intake.spin(reverse, 100, percent);
  } else {
    Intake.stop(hold);
  }

  if(Controller1.ButtonL1.pressing()) {
   // Lift.spin(forward, 50, percent);
    Tilter.spin(forward, 100, percent);
    if(Lift.rotation(degrees) >= MAX_LIFT_ROTATION) {
      Lift.stop(hold);
    }
    if(Tilter.rotation(degrees) >= MAX_TILT_ROTATION) {
      Tilter.stop(hold);
    }
  } else if (Controller1.ButtonL2.pressing()) {
 //   Lift.spin(reverse, 50, percent);
    Tilter.spin(reverse, 100, percent);
    if(Tilter.rotation(degrees) <= 10) {
      Tilter.stop(hold);
    }
    if(Lift.rotation(degrees) <= 10) {
      Lift.stop(hold);
    }
  } else {
    Lift.stop(hold);
    Tilter.stop(hold);
  }
  
  while(1) {
    double leftVelocity = Controller1.Axis3.position(percent);
    double rightVelocity = Controller1.Axis2.position(percent);

    Left.spin(forward, leftVelocity, percent);
    Right.spin(forward, rightVelocity, percent);

    if(leftVelocity < 2 & leftVelocity > -2) {
      Left.stop(coast);
    }
    if(rightVelocity < 2 & rightVelocity > -2) {
      Right.stop(coast);
    }
  }
}
