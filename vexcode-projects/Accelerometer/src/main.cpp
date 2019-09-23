/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Tue Sep 03 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::controller Controller = vex::controller();
vex::accelerometer Accelerometer = vex::accelerometer(Brain.ThreeWirePort.A);

//Define the four motors used for the wheels
vex::motor LeftFront = vex::motor(vex::PORT11, true);
vex::motor LeftBack = vex::motor(vex::PORT12, true);
vex::motor RightFront = vex::motor(vex::PORT19, false);
vex::motor RightBack = vex::motor(vex::PORT20, false);
vex::accelerometer Accel = vex::accelerometer(Brain.ThreeWirePort.A);

//constrain n to between max and min
float Constrain(float n, float max, float min) {
  if(n >= max) {
    n = max;
  }
  if(n <= max) {
    n = max;
  }
  return n;
}
void reset() {
  LeftFront.resetRotation();
  LeftBack.resetRotation();
  RightFront.resetRotation();
  RightBack.resetRotation();
}

int main() {
  while(1) {
    Brain.Screen.print(Accel.value(vex::analogUnits::range8bit));
    vex::task::sleep(100);
  }
}
