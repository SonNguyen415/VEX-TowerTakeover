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
// LeftLift             motor         11              
// RightLift            motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void SetLiftVelocity(float velocity) {
  LeftLift.setVelocity(velocity, percent);
  RightLift.setVelocity(velocity, percent);
}

void Up() {
  SetLiftVelocity(50);
  LeftLift.spin(forward);
  RightLift.spin(forward);
}

void Down() {
  SetLiftVelocity(50);
  LeftLift.spin(reverse);
  RightLift.spin(reverse);
}

void Halt() {
  LeftLift.setStopping(hold);
  RightLift.setStopping(hold);
  LeftLift.stop();
  RightLift.stop();  
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Controller1.ButtonR1.pressed(Up);
  Controller1.ButtonR2.pressed(Down);
  Controller1.ButtonR1.released(Halt);
  Controller1.ButtonR2.released(Halt);
  while(1) {
    Left.setVelocity(Controller1.Axis3.position(percent), percent);
    Right.setVelocity(Controller1.Axis2.position(percent), percent);
    Left.spin(forward);
    Right.spin(forward);
  }
}
