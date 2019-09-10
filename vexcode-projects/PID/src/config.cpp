#include "vex.h"
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::controller Controller = vex::controller();

//Define the four motors used for the wheels
vex::motor LeftFront = vex::motor(vex::PORT11, true);
vex::motor LeftBack = vex::motor(vex::PORT12, true);
vex::motor RightFront = vex::motor(vex::PORT19, false);
vex::motor RightBack = vex::motor(vex::PORT20, false);

//Define the motor for the lift system
vex::motor LiftMotor = vex::motor(vex::PORT3, true);