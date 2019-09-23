/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Tue Sep 03 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "auton.cpp"

int main() {
  Move(1000, 1000, 50);
  Controller.ButtonL1.pressed(Forward);
  Controller.ButtonR1.pressed(Backward);
  // Controller.ButtonL1.pressed(Faster);
  // Controller.ButtonL2.pressed(Slower);
  // Controller.ButtonR1.pressed(RaiseArm);
  // Controller.ButtonR2.pressed(LowerArm);
  // Controller.ButtonR1.released(StopArm);
  // Controller.ButtonR2.released(StopArm);
  while(1) {
    LeftFront.spin(directionType::fwd, Controller.Axis2.position() * speed_modifier, velocityUnits::pct);
    LeftBack.spin(directionType::fwd, Controller.Axis2.position() * speed_modifier, velocityUnits::pct);
    RightFront.spin(directionType::fwd, Controller.Axis3.position() * speed_modifier, velocityUnits::pct);
    RightBack.spin(directionType::fwd, Controller.Axis3.position() * speed_modifier, velocityUnits::pct);
  }
}