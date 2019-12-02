/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Thu Nov 07 2019                                           */
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
// Motor                motor         5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

int main() {
  // Initializing Robot Configuration.
  vexcodeInit();
 
  const int kP = 5; //A constant to control the proportional speed
  const float destination = 500; //The final destination
  Motor.resetRotation();
  while(1) {
    //Sensor input
    double currentRotation = Motor.rotation(degrees); 

    //Computation
    double error = destination - currentRotation;
    double motorVelocity = error / kP;

    //Actuating the actuator
    Motor.spin(forward, motorVelocity, percent);
  } 
}