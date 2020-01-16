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

//Constants:
const double INTAKE_VELOCITY = 100;

void intake() {
  Intake.spin(forward, INTAKE_VELOCITY, percent);
}

void outake() {
  Intake.spin(reverse, INTAKE_VELOCITY, percent);
}

void roller_stop() {
  Intake.stop(hold);
}

void tilter_forward(){
  Tilter.spin(forward, TILTER_VELOCITY, percent);
}

void tilter_backward(){
  Tilter.spin(reverse, TILTER_VELOCITY, percent);
}

void tilter_hold(){
  Tilter.stop(hold);
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
  Controller.ButtonUp.pressed(faster);
  Controller.ButtonDown.pressed(slower);

  Controller.ButtonR1.pressed(intake);
  Controller.ButtonR2.pressed(outake);
  Controller.ButtonR1.released(roller_stop);
  Controller.ButtonR2.released(roller_stop);

  Controller.ButtonL1.pressed(tilter_forward);
  Controller.ButtonL2.pressed(tilter_backward);
  Controller.ButtonL1.released(tilter_hold);
  Controller.ButtonL2.released(tilter_hold);

  Controller.ButtonB.pressed(arms_to_bottom);
  Controller.ButtonA.pressed(arms_to_middle);
  Controller.ButtonX.pressed(arms_to_high);


  while (1) {
    Left.spin(forward, Controller.Axis3.value() * speedMod, percent); //(Axis3+Axis4)/2
    Right.spin(forward, Controller.Axis2.value() * speedMod, percent);

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

