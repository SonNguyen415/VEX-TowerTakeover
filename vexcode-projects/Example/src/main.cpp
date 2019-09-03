/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Sun Sep 01 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;


//Define new objects such as motors, brains, and controllers
vex::brain       Brain;
vex::controller Controller = vex::controller();
vex::motor Motor = vex::motor(vex::PORT11);

//Define a variable n, float is a type of number that enable decimal point and larger numbers
float n = 38.48;

//Define a new boolean variable, booleans only give you true or false
bool stop = false;

//Define a new i variable, int is short for integer, allowing no decimal numbers
int i = 1;

void forward() { //go forward n degree at 50% velocity, n is predefined above
  Motor.rotateFor(n,vex::rotationUnits::deg,50,vex::velocityUnits::pct);
}

int main() {
  forward(); //calls the function go forward
  
  //This makes a loop that run as long as stop = false
  while(stop == false) {
    //Go forward at 50 rotation / minute
    Motor.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm); 

    i = i + 1; 
    //Each time the program goes through this loop, i will be added 1 each time, 
    //if you have physics it's like the V in Vf = Vi + at

    if(i == 10) {
      stop = true; //Makes the stop boolean false so the while loop stops
    }
  }
}
