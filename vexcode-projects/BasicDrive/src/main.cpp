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
vex::motor LeftFront = vex::motor(vex::PORT1, true);
vex::motor LeftBack = vex::motor(vex::PORT2, true);
vex::motor RightFront = vex::motor(vex::PORT3, false);
vex::motor RightBack = vex::motor(vex::PORT4, false);


int main() {
   
    while(1) {
        // Allow other tasks to run
        LeftFront.spin(directionType::fwd, Controller.Axis2.position(), velocityUnits::pct);
        LeftFront.spin(directionType::fwd, Controller.Axis2.position(), velocityUnits::pct);
        RightFront.spin(directionType::fwd, Controller.Axis3.position(), velocityUnits::pct);
        RightBack.spin(directionType::fwd, Controller.Axis3.position(), velocityUnits::pct);
        this_thread::sleep_for(10);
    }
}
