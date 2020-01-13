/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Tue Jan 07 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// L1                   motor         1               
// L2                   motor         2               
// R1                   motor         3               
// R2                   motor         4               
// I1                   motor         5               
// I2                   motor         6               
// Lift                 motor         7               
// Tilter               motor         8               
// Drivetrain           drivetrain    9, 10, 11, 12, B
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

motor_group Left(L1, L2);
motor_group Right(R1, R2);
motor_group DriveBase(L1, L2, R1, R2);


double constrain (double constrainedValue, double maxValue, double minValue) {
  if(constrainedValue > maxValue) {
    return maxValue;
  }
  if(constrainedValue < minValue) {
    return minValue;
  }
  return constrainedValue;
}

void auton() {
  double midPoint = 500;
  double endPoint = 1000;
  double maxVelocity = 80;

  double motorRotation = DriveBase.rotation(deg);
  double motorVelocity = 0;
  double kP = 2;
  
  //Accelerate until mid point
  while (motorRotation < midPoint) {
    double error = midPoint - motorRotation;
    motorVelocity = kP / error;
    motorVelocity = constrain(motorVelocity, maxVelocity, -maxVelocity);
    DriveBase.spin(forward, motorVelocity, percent);
  }

  //Deccelerate until end point
  while (motorRotation < endPoint) {
    double error = endPoint - motorRotation;
    motorVelocity = error * kP;
    motorVelocity = constrain(motorVelocity, maxVelocity, -maxVelocity);
    DriveBase.spin(forward, motorVelocity, percent);
  }
  return;
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  auton();
}
