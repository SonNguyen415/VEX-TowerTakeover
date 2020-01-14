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
  if(constrainedValue < minValue && constrainedValue >= 0) {
    Brain.Screen.printAt(1, 120, "Less than 1");
    return minValue;
  }
  if(constrainedValue > -minValue && constrainedValue <= 0) {
    Brain.Screen.printAt(1, 120, "Less than 0");
    return -minValue;
  }
  return constrainedValue;
}

void auton() {
  double midPoint = 500;
  double maxVelocity = 80;
  double minVelocity = 2;

  double motorRotation = DriveBase.rotation(deg);
  double motorVelocity = 1;
  double kP = 8;
  double kD = 4;
  double oldRotation = motorRotation;

  //Accelerate until mid point
  while (motorRotation < midPoint) {
    motorRotation = DriveBase.rotation(deg);
    double dRotation = motorRotation - oldRotation;
    motorVelocity = motorRotation / kP -  dRotation / kD;
  /*  if (error != 0) {
      motorVelocity = kP / sqrt(error);
    } else {
      motorVelocity = 0;
    }*/
    motorVelocity = constrain(motorVelocity, maxVelocity, minVelocity);
    DriveBase.spin(forward, motorVelocity, percent);
    Brain.Screen.printAt(1, 40, "%f", motorVelocity);
    Brain.Screen.printAt(1, 80, "%f", motorRotation);

    oldRotation = motorRotation;
  }
  DriveBase.stop(coast);
  while(1) {
    motorRotation = DriveBase.rotation(deg);
    Brain.Screen.printAt(1, 80, "%f", motorRotation);
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
