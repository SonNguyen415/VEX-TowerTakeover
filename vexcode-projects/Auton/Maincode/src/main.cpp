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
//#include "auton.cpp"

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
  Mover.setVelocity(30, percent);
  Grip.setVelocity(40, percent);
  Mover.spinFor(forward, 120, rotationUnits::deg, false);
  L.spinFor(forward, (1.5*360), rotationUnits::deg, 80, velocityUnits::pct, false);
  R.spinFor(forward, (1.5*360), rotationUnits::deg, 80, velocityUnits::pct, true);
  wait(0.2, timeUnits::sec);
  DriveTrain.driveFor(reverse, 28, distanceUnits::cm, 50, velocityUnits::pct,true);
  Grip.spin(forward);
  Mover.spinFor(forward, -120, rotationUnits::deg, true);
  wait(0.1, timeUnits::sec);
  Grip.setPosition(0,degrees);
  Grip.stop(brake);
  Grip.rotateTo(-70, degrees);
  R.spinFor(reverse, ((22)/(10.16)), rotationUnits::rev, 50, velocityUnits::pct, true);
  DriveTrain.driveFor(forward, 45, distanceUnits::cm, 40, velocityUnits::pct,true);
  wait(0.5, sec);
  Grip.spin(forward);
  wait(0.2, timeUnits::sec);
  Mover.spinFor(forward,400, rotationUnits::deg, true);
  DriveTrain.driveFor(reverse, 9, distanceUnits::cm, 40, velocityUnits::pct,true);
  L.spinFor(reverse, ((22)/(10.16)), rotationUnits::rev, 50, velocityUnits::pct, true);
  DriveTrain.driveFor(forward, 80, distanceUnits::cm, 30, velocityUnits::pct);
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
      Grip.stop(brakeType::brake);
    }
  }
}
