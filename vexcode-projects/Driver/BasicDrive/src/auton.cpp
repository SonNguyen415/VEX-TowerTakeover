#include "vex.h"
motor_group Left(L1, L2); //Group the left wheels into one group
motor_group Right(R1, R2); //Group the right wheels into one group
motor_group Lift(A1, A2); //Group the lift motors into one group
motor_group Intake(I1, I2); //Group the intake motors into one group

using namespace vex;

int IDLE = 0;
int MOVING = 1;

int state = IDLE;
int count = 0;

void updateState() {
  count = count + 1;

}

int evaluateState() {
  if (state == IDLE) {
    return IDLE;
  }
  else {
    return MOVING;
  }
}

void reactToState() {

}

void auton() {

}