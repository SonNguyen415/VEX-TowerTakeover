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
// L1                   motor         11              
// L2                   motor         19              
// R1                   motor         20              
// R2                   motor         4               
// Drivetrain           drivetrain    10, 9, G        
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "robot-config.cpp"
using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while (1) {
    //The velocity is equated to the joystick position
    double left_velocity = Controller1.Axis3.position(pct);
    double right_velocity = Controller1.Axis2.position(pct);    
    
    Left.spin(forward, left_velocity, pct);
    Right.spin(forward, right_velocity, pct);
  }
} 



