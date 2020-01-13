#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

// VEXcode device constructors


//Ratio 36_1 = 100 rpm motors
motor I1 = motor(PORT10, ratio36_1, false); 
motor I2 = motor(PORT20, ratio36_1, true);


//Normal 300 rpm motors
motor Lift = motor(PORT19, ratio18_1, false);
motor Tilter = motor(PORT13, ratio18_1, false);

//Left motor groups
motor L1 = motor(PORT1, ratio18_1, false);
motor L2 = motor(PORT11, ratio18_1, false);

//Right motor groups
motor R1 = motor(PORT10, ratio18_1, true);
motor R2 = motor(PORT12, ratio18_1, true);


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}