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
// Drivetrain           drivetrain    3, 4, C         
// Left                 motor         12              
// Right                motor         5               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Drivetrain.drive(forward);

  while (1) {
    //The velocity is equated to the joystick position
    double left_velocity = Controller1.Axis3.position(pct);
    double right_velocity = Controller1.Axis2.position(pct);    
    
    Left.spin(forward, left_velocity, pct);
    Right.spin(forward, right_velocity, pct);
  }
} 



