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
// L2                   motor         11              
// R1                   motor         2               
// R2                   motor         12              
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
  if(constrainedValue < -maxValue) {
    return -maxValue;
  }
  if(constrainedValue < minValue && constrainedValue > 0) {
    return minValue;
  }
  if(constrainedValue > -minValue && constrainedValue < 0) {
    return -minValue;
  }
  return constrainedValue;
}

void auton() {
  double midPoint = 500;
  double endPoint = 1000;
  double maxVelocity = 80;
  double minVelocity = 1;

  double motorRotation = DriveBase.rotation(deg);
  double motorVelocity = 1;
  double kP = 30;
  double oldError = 0;
  
  //Accelerate until mid point
  while (motorRotation < midPoint) {
    motorRotation = DriveBase.rotation(deg);
    double error = midPoint - motorRotation;
    double errorChange = abs(oldError - error);
    motorVelocity += errorChange / kP;
  /*  if (error != 0) {
      motorVelocity = kP / sqrt(error);
    } else {
      motorVelocity = 0;
    }*/
    motorVelocity = constrain(motorVelocity, maxVelocity, minVelocity);
    Left.spin(forward, motorVelocity, percent);
    Right.spin(forward, motorVelocity, percent);
    Brain.Screen.printAt(1, 40, "%f", motorVelocity);
    Brain.Screen.printAt(1, 80, "%f", error);
    Brain.Screen.printAt(1, 120, "%f", error);

    oldError = error;
  }

  /*
  //Deccelerate until end point
  while (motorRotation < endPoint) {
    double error = endPoint - motorRotation;
    motorVelocity = error * kP;
    motorVelocity = constrain(motorVelocity, maxVelocity, -maxVelocity);
    DriveBase.spin(forward, motorVelocity, percent);
  }
  */
  return;
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  auton();
}
