/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Fri Nov 22 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Lift1                motor         11              
// Controller1          controller                    
// Lift2                motor         1               
// Left                 motor         20              
// Right                motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

double TOLERANCE = 10;

double constrain(double myValue, double max, double min) {
  if(myValue >= max) {
    return max;
  }
  if(myValue <= min) {
    return min;
  }
  return myValue;
}

void reset() {
  Lift1.resetRotation();
  Lift2.resetRotation();
}

void moveMotor(double setPoint) {
  reset();
  double kP = 5;
  while(1) {
    double rotation1 = Lift1.rotation(degrees);
    double rotation2 = Lift2.rotation(degrees);

    double error1 = setPoint - rotation1;
    double error2 = setPoint - rotation2;
    
    double error = (error1 + error2) / 2;
    double motorVelocity = error / kP;
    motorVelocity = constrain(motorVelocity, 80, -80);
    
    Lift1.spin(forward, motorVelocity, percent);
    Lift2.spin(forward, motorVelocity, percent);

    Brain.Screen.printAt(1, 50, "%6.1f", Lift1.velocity(percent));
    Brain.Screen.printAt(1, 80, "%6.1f", Lift2.velocity(percent));

    if(error > -TOLERANCE && error < TOLERANCE) {
      Lift1.stop(coast);
      Lift2.stop(coast);
      Brain.Screen.printAt(1, 100, "Done");
      return;
    }
  }
}

void raiseLift() {
  Brain.Screen.printAt(1, 20, "Process start");
  moveMotor(2500);
}

void lowerLift() {
  moveMotor(-2500);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Controller1.ButtonUp.pressed(raiseLift);
  Controller1.ButtonDown.pressed(lowerLift);

  while(1) {

    Left.spin(forward, Controller1.Axis3.position(), percent);
    Right.spin(forward, Controller1.Axis2.position(), percent);
  }

}
