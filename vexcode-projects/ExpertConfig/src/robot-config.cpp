#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

// VEXcode device constructors


//Ratio 36_1 = 100 rpm motors
motor I1 = motor(PORT5, ratio36_1, false); 
motor I2 = motor(PORT6, ratio36_1, true);

//Normal 300 rpm motors
motor Lift = motor(PORT7, ratio18_1, false);
motor Tilter = motor(PORT8, ratio18_1, false);

//Left motor groups
motor L1 = motor(PORT1, ratio18_1, false);
motor L2 = motor(PORT2, ratio18_1, false);
motor_group Left = motor_group(L1, L2);


//Right motor groups
motor R1 = motor(PORT3, ratio18_1, true);
motor R2 = motor(PORT4, ratio18_1, true);
motor_group Right = motor_group(R1, R2);


//Drivetrain motor(left, right, wheelSize, trackWidth, wheelBase, baseUnit, externalGearRatio)
drivetrain Drivetrain = drivetrain(Left, Right, 299.24, 295, 165, mm, 1);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}