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

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

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

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Grip.setPosition(0,degrees);
  Grip.spinTo(-50, rotationUnits::deg, 50, velocityUnits::pct);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
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
  Grip.rotateTo(-50, degrees);
  L.spin(reverse, 50, percentUnits::pct);
  wait(3, timeUnits::sec);
  L.stop(brakeType::hold);
  DriveTrain.driveFor(forward, 45, distanceUnits::cm, 40, velocityUnits::pct,true);
  Grip.spin(forward);
  wait(0.2, timeUnits::sec);
  Mover.spinFor(forward,120, rotationUnits::deg, true);
  DriveTrain.driveFor(reverse, 45, distanceUnits::cm, 40, velocityUnits::pct,true);
  L.spinFor(forward, ((22/10.16)-0.1), rotationUnits::rev, 80, velocityUnits::pct);
  Grip.stop(brakeType::undefined);
  DriveTrain.driveFor(forward, 40, distanceUnits::cm, 100, velocityUnits::pct);
  DriveTrain.driveFor(forward, -30, distanceUnits::cm, 30, velocityUnits::pct);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  
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
      Grip.rotateTo(-50, degrees);
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
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
