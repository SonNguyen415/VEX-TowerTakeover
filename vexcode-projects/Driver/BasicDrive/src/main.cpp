/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Sat Nov 02 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// L1                   motor         1               
// L2                   motor         2               
// R1                   motor         3               
// R2                   motor         4               
// A1                   motor         5               
// A2                   motor         6               
// I1                   motor         7               
// I2                   motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "auton.cpp"

double LIFT_SPEED = 50; //Define the lift speed as a constant in percentage
double INTAKE_SPEED = 50; //Define the intake speed as a constant in percentage

//Global variables
float speed_modifier = 0.5;

//Constrain an input value between two min and max values
double constrain(double input, double max, double min) {
  if (input > max) {
    return max;
  }
  if (input < max) {
    return min;
  }
  return input;
}

//Set stopping mode for the base to be coast (no active brake)
void setBrakeMode() {
  Left.setStopping(coast);
  Right.setStopping(coast);
}

//Go faster
void increaseSpeed() {
  speed_modifier = speed_modifier + 0.25;
  speed_modifier = constrain(speed_modifier, 1, 0);
}

//Go slower
void decreaseSpeed() {
  speed_modifier = speed_modifier - 0.25;
  speed_modifier = constrain(speed_modifier, 1, 0);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  setBrakeMode();

  Controller1.ButtonUp.pressed(increaseSpeed);
  Controller1.ButtonDown.pressed(decreaseSpeed);

  while (1) {
    //Controller Button Rs will spin the lift motors when held
    if(Controller1.ButtonR1.pressing()) {
      Lift.spin(forward, LIFT_SPEED, pct);
    } else if (Controller1.ButtonR2.pressing()) {
      Lift.spin(reverse, LIFT_SPEED, pct);
    } else {
      Lift.stop(hold);
    }

    //Controller Button Ls will spin the intake motors when held
    if(Controller1.ButtonL1.pressing()) {
      Intake.spin(forward, INTAKE_SPEED, pct);
    } else if (Controller1.ButtonL2.pressing()) {
      Intake.spin(reverse, INTAKE_SPEED, pct);
    } else {
      Intake.stop(hold);
    }

    //The velocity is equated to the joystick position
    double left_velocity = Controller1.Axis2.position(pct);
    double right_velocity = Controller1.Axis3.position(pct);    
    Left.spin(forward, left_velocity, pct);
    Right.spin(forward, right_velocity, pct);
  }
}
