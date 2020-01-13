#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Arm = motor(PORT1, ratio36_1, false);
motor IntakeLeft = motor(PORT2, ratio18_1, false);
motor IntakeRight = motor(PORT3, ratio18_1, true);
motor Tilter = motor(PORT10, ratio36_1, true);
motor BackLeft = motor(PORT11, ratio18_1, false);
motor FrontLeft = motor(PORT12, ratio18_1, true);
motor FrontRight = motor(PORT18, ratio18_1, false);
motor BackRight = motor(PORT19, ratio18_1, true);
controller Controller1 = controller(primary);
gyro Gyro = gyro(Brain.ThreeWirePort.H);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}