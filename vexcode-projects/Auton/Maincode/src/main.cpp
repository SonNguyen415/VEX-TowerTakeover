/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       apple                                                     */
/*    Created:      Mon Dec 02 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// R                    motor         10              
// L                    motor         20              
// M1                   motor         1               
// M2                   motor         11              
// Grip                 motor         2               
// Gyro                 gyro          A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
motor_group Mover(M1,M2);
smartdrive DriveTrain= smartdrive(L, R, Gyro, 319.19, 320, 130, mm, 1);

float speedModifier = 0.5;


void Faster() {
  speedModifier = speedModifier + 0.2;
  if (speedModifier > 1){
     speedModifier = 1;
  }
}

void Slower() {
  speedModifier = speedModifier - 0.2;
  if (speedModifier < 0.1){
     speedModifier = 0.1;
  }
}

void Auton() {
  L.spinFor(forward, (2.3*360), rotationUnits::deg, 50, velocityUnits::pct, false);
  R.spinFor(forward, (2.3*360), rotationUnits::deg, 50, velocityUnits::pct, false);
  /*Mover.setVelocity(50, percent);
  Grip.setVelocity(40, percent);
  Grip.rotateTo(-40,degrees);
  DriveTrain.driveFor(forward, 25, distanceUnits::cm, 50, velocityUnits::pct);
  Grip.spin(forward, 50, percent);
  Mover.rotateFor(500, degrees);
  L.*/

}



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Grip.setPosition(0,degrees);
  Grip.setVelocity(40, percent);
  Mover.setVelocity(50, percent);

  
  Mover.rotateFor(50, degrees);
  DriveTrain.driveFor(forward, 69, distanceUnits::cm, 50, velocityUnits::pct);
 


  Controller1.ButtonA.pressed(Faster);
  Controller1.ButtonB.pressed(Slower);

  while (1) {
    Brain.Screen.printAt(1, 40, "%6.1f", L.rotation(degrees));
    Brain.Screen.printAt(1, 80, "%6.1f", R.rotation(degrees));

    R.spin(forward, Controller1.Axis2.position(percent) * speedModifier, percent);
    L.spin(forward, Controller1.Axis3.position(percent) * speedModifier, percent);

    
    if (Controller1.ButtonR1.pressing()){
      Mover.spin(forward, 50, percent);
    }
    else if (Controller1.ButtonR2.pressing()){
      Mover.spin(forward, -50, percent);
    }
    else{
      Mover.stop(hold);
    }
    if (Controller1.ButtonL1.pressing()){
      Grip.spin(forward);
    }
    else if(Controller1.ButtonL2.pressing()){
      Grip.rotateTo(-40, degrees);
    }
  }
}
