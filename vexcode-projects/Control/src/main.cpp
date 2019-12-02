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
// Lift1                motor         10              
// Lift2                motor         20              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "math.h"

using namespace vex;

const float TOLERANCE = 10;

void reset() {
  Lift1.setPosition(0, degrees);
  Lift2.setPosition(0, degrees);
}

float constrain(float constrainedValue, float max, float min) {
  if(constrainedValue > max) {
    return max;
  }else if(constrainedValue < min) {
    return min;
  }
  return constrainedValue;
}

void goToHigh() {
  double setPoint = 600;
  double kP = 5;

  while(1) {
    double rotation1 = Lift1.rotation(vex::rotationUnits::deg);
    double rotation2 = Lift2.rotation(vex::rotationUnits::deg);

    double error = setPoint - (rotation1 +rotation2)/2;
    double motorVelocity = error / kP;
    motorVelocity = constrain(motorVelocity, 100, -100);

    Lift1.spin(vex::directionType::fwd, motorVelocity, vex::velocityUnits::pct); 
    Lift2.spin(vex::directionType::fwd, motorVelocity, vex::velocityUnits::pct);

    if(error > -TOLERANCE && error < TOLERANCE) {
      Brain.Screen.printAt(1, 130, "Done");
      break;
    }
  }
  return;
}

void goToLow() {

}

void Stop() {
  Lift1.stop(hold);
  Lift2.stop(hold);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  reset();

  Lift1.setMaxTorque(100, percent);
  Lift2.setMaxTorque(100, percent);

  Controller1.ButtonA.pressed(goToHigh);
  Controller1.ButtonB.pressed(goToLow);

  while(1) {
    if(Controller1.ButtonR1.pressing()) {
      Lift1.spin(forward, 50, percent);
      Lift2.spin(forward, 50, percent);
    }else if(Controller1.ButtonR2.pressing()){
      Lift1.spin(forward, -50, percent);
      Lift2.spin(forward, -50, percent); 
    }else {
      Stop();
    }
  }
}
