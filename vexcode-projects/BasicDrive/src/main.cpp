/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Mon Aug 19 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// define your global instances of motors and other devices here
vex::brain       Brain;
vex::controller Controller = vex::controller();
vex::motor LeftFront = vex::motor(vex::PORT11, false);
vex::motor LeftBack = vex::motor(vex::PORT20, false);
vex::motor RightFront = vex::motor(vex::PORT1, true);
vex::motor RightBack = vex::motor(vex::PORT10, true);


int main() {
    while(1) {
        // Allow other tasks to run
        RightFront.spin(vex::directionType::fwd, Controller.Axis2.position(), vex::velocityUnits::pct);
        RightBack.spin(vex::directionType::fwd, Controller.Axis2.position(), vex::velocityUnits::pct);
        LeftFront.spin(vex::directionType::fwd, Controller.Axis3.position(), vex::velocityUnits::pct);
        LeftBack.spin(vex::directionType::fwd, Controller.Axis3.position(), vex::velocityUnits::pct);
        this_thread::sleep_for(10);
    }
}
