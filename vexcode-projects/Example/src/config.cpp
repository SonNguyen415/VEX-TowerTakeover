#include "vex.h"

using namespace vex;

//Define a VEX Brain
vex::brain       Brain;

//Define a VEX controller
vex::controller Controller = vex::controller();

//Define a motor, its port, and if its direction is reversed
vex::motor LeftMotor = vex::motor(vex::PORT11, false); //Not reversed
vex::motor RightMotor = vex::motor(vex::PORT11, true); //Reversed