#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor R = motor(PORT10, ratio18_1, true);
motor L = motor(PORT20, ratio18_1, false);
motor M1 = motor(PORT1, ratio18_1, true);
motor M2 = motor(PORT11, ratio18_1, false);
motor Grip = motor(PORT2, ratio18_1, true);
gyro Gyro = gyro(Brain.ThreeWirePort.A);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}