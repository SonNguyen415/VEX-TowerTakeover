#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor L1 = motor(PORT11, ratio18_1, false);
motor L2 = motor(PORT19, ratio18_1, false);
motor R1 = motor(PORT20, ratio18_1, true);
motor R2 = motor(PORT4, ratio18_1, true);
gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.G);

motor_group Left(L1, L2); //Group the left wheels into one group
motor_group Right(R1, R2); //Group the right wheels into one group
smartdrive Drivetrain= smartdrive(Left, Right, TurnGyroSmart, 319.19, 320, 130, mm, 1);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.calibrate();
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}