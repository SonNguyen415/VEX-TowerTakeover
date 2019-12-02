/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Thu Oct 31 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Left                 motor         20              
// Right                motor         10              
// Lift1                motor         11              
// Lift2                motor         1               
// Intake               motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

motor_group Lift(Lift1, Lift2);
double speedModifier = 1;

void Faster() {
  speedModifier += 0.2;
  if (speedModifier > 1) {
    speedModifier = 1;
  }
}

void Slower() {
  speedModifier -= 0.2;
  if (speedModifier < 0.1) {
    speedModifier = 0.1;
  }
}

void openClaw() {
  Intake.rotateTo(50, rotationUnits::deg, 100, velocityUnits::pct);
}

void closeClaw() {
  Intake.rotateTo(0, rotationUnits::deg, 100, velocityUnits::pct);
}

void Up() {
  Lift.spin(forward, 50, percent);
}

void Down() {
  Lift.spin(reverse, 50, percent);
}

void Halt() {
  Lift.stop(hold);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Intake.resetRotation();

  Controller1.ButtonR1.pressed(Up);
  Controller1.ButtonR2.pressed(Down);
  Controller1.ButtonR1.released(Halt);
  Controller1.ButtonR2.released(Halt);

  Controller1.ButtonL1.pressed(openClaw);
  Controller1.ButtonL2.pressed(closeClaw);

  Controller1.ButtonUp.pressed(Faster);
  Controller1.ButtonDown.pressed(Slower);
  
  while(1) {
    Left.spin(forward, Controller1.Axis3.position(percent) * speedModifier, percent);
    Right.spin(forward, Controller1.Axis2.position(percent) * speedModifier, percent);
  }
}
