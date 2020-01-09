#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor L1 = motor(PORT1, ratio18_1, false);
motor L2 = motor(PORT2, ratio18_1, false);
motor R1 = motor(PORT3, ratio18_1, true);
motor R2 = motor(PORT4, ratio18_1, true);
motor I1 = motor(PORT5, ratio36_1, false);
motor I2 = motor(PORT6, ratio36_1, true);
motor Lift = motor(PORT7, ratio18_1, false);
motor Tilter = motor(PORT8, ratio18_1, false);
motor leftMotorA = motor(PORT9, ratio18_1, false);
motor leftMotorB = motor(PORT10, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);

motor rightMotorA = motor(PORT11, ratio18_1, true); 
motor rightMotorB = motor(PORT12, ratio18_1, true); 
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);

drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 165, mm, 1);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}