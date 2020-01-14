/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// L1                   motor         1               
// L2                   motor         11              
// R1                   motor         2               
// R2                   motor         12              
// I1                   motor         10              
// I2                   motor         20              
// Tilter               motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "auton.h"

using namespace vex;

void faster() {

}

void slower() {
  
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Left.setPosition(0, rotationUnits::deg);
  Right.setPosition(0, rotationUnits::deg);

  Left.setRotation(0, rotationUnits::deg);
  Right.setRotation(0, rotationUnits::deg);

  Left.setStopping(coast);
  Right.setStopping(coast);
  Intake.setStopping(hold);
}

void autonomous(void) {
  move(10, 10, 10, 10);//Move forward
  eat_cube(500, false);
  move(-10, -10, 10, 10); //Move backward
  move(10, 10, 10, 10); //Turn
  move(10, 10, 10, 10); //Move forward a lil
  score();
  move(-10, -10, 10, 10); //Move backward a lil
}


void usercontrol(void) {
  while (1) {

    wait(20, msec); 
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
