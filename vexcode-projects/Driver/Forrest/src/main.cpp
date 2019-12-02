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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

motor_group Lift(Lift1, Lift2);

using namespace vex;

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
  Controller1.ButtonR1.pressed(Up);
  Controller1.ButtonR2.pressed(Down);
  Controller1.ButtonR1.released(Halt);
  Controller1.ButtonR2.released(Halt);

  
  while(1) {
    Left.setVelocity(Controller1.Axis3.position(percent), percent);
    Right.setVelocity(Controller1.Axis2.position(percent), percent);
    Left.spin(forward);
    Right.spin(forward);

    Brain.Screen.print(Lift1.rotation(degrees));
    Brain.Screen.print(Lift2.rotation(degrees));
  }
}
