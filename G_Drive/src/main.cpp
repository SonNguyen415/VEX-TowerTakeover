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
// Arm                  motor         1               
// IntakeLeft           motor         2               
// IntakeRight          motor         3               
// Tilter               motor         10              
// FrontLeft            motor         12              
// BackLeft             motor         11              
// FrontRight           motor         18              
// BackRight            motor         19              
// Controller1          controller                    
// Gyro                 gyro          H               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       SeJin Kim                                              */
/*    Created:      Wed Dec 4 2019                                           */
/*    Description:  Control Loop + auton for 76209G                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"

using namespace vex;

motor_group Left(FrontLeft,BackLeft);
motor_group Right(FrontRight, BackRight);
motor_group IntakeMotors(IntakeLeft, IntakeRight);

smartdrive DriveTrain= smartdrive(Left, Right, Gyro, 319.19, 320, 130, mm, 1);

bool GOING_UP = true;

int IntakeVelocity = 100;

float tilterSetPoint = 100;
float TilterVelocity = 30;

int Tolerance = 5;
float kP = 4;
int MaxPositiveVelocity = 50;
int MaxNegativeVelocity = -50;

void moveArm(float setPoint) {

  while(true) {
    float error = setPoint - Arm.rotation(degrees);
    float MotorVelocity = error / kP;

    if(MotorVelocity > MaxPositiveVelocity){
      MotorVelocity = MaxPositiveVelocity;
    }
    else if (MotorVelocity < MaxNegativeVelocity){
      MotorVelocity = MaxNegativeVelocity;
    }
    
    if (GOING_UP) {
      Tilter.rotateTo(tilterSetPoint, degrees, TilterVelocity, velocityUnits::pct, false);
    } else {
      Tilter.rotateTo(0, degrees, TilterVelocity, velocityUnits::pct, false);
    }

    Arm.spin(forward, MotorVelocity, percent);

    if(error > -Tolerance && error < Tolerance){
      break;
    }
    Controller1.Screen.print("one sec Process complete");
      wait(1, seconds);
      Arm.stop(hold);
      return;
  }
}

void ArmsToBottom() {
  GOING_UP = false;
  moveArm(0);
}

void ArmsToMiddle() {
  GOING_UP = true;
  moveArm(200);
}

void ArmsToHigh() {
  GOING_UP = true;
  moveArm(400);
}

void Intake(){
  IntakeMotors.spin(forward, IntakeVelocity, percent);
}

void Outtake(){
  IntakeMotors.spin(reverse, IntakeVelocity, percent);
}

void RollersStop(){
  IntakeMotors.stop(hold);
}

void TilterForward(){
  Tilter.spin(forward, 20, percent);
}

void TilterBack(){
  Tilter.spin(reverse, 20, percent);
}

void TilterHold(){
  Tilter.stop(hold);
}


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

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

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
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  FrontLeft.spinFor(-1080, degrees, false);
  FrontRight.spinFor(-1080, degrees, false);
  BackRight.spinFor(-1080, degrees, false);
  BackLeft.spinFor(-1080, degrees, true);

  FrontLeft.spinFor(1080, degrees, false);
  FrontRight.spinFor(1080, degrees, false);
  BackRight.spinFor(1080, degrees, false);
  BackLeft.spinFor(1080, degrees, false);
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
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    //Arm control:

  Controller1.ButtonB.pressed(ArmsToBottom);
  Controller1.ButtonA.pressed(ArmsToMiddle);
  Controller1.ButtonX.pressed(ArmsToHigh);

  Controller1.ButtonR2.pressed(Intake);
  Controller1.ButtonR1.pressed(Outtake);
  Controller1.ButtonR2.released(RollersStop);
  Controller1.ButtonR1.released(RollersStop);

  Controller1.ButtonL2.pressed(TilterForward);  
  Controller1.ButtonL1.pressed(TilterBack);  
  Controller1.ButtonL2.released(TilterHold);
  Controller1.ButtonL1.released(TilterHold);


  while(true) {
    FrontLeft.spin(forward, Controller1.Axis3.value(), percent); //(Axis3+Axis4)/2
    BackLeft.spin(forward, Controller1.Axis3.value(), percent); //(Axis3+Axis4)/2
    FrontRight.spin(forward, Controller1.Axis2.value(),percent);//(Axis3-Axis4)/2
    BackRight.spin(forward, Controller1.Axis2.value(), percent); //(Axis3+Axis4)/2
  }

  while(1) {
    Brain.Screen.print(Arm.rotation(degrees));
    Controller1.Screen.print(Arm.velocity(percent));
  }
    // ........................................................................

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
