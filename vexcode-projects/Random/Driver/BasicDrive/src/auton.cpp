#include "vex.h"
motor_group Left(L1, L2); //Group the left wheels into one group
motor_group Right(R1, R2); //Group the right wheels into one group
motor_group Intake(Intake1, Intake2); //Group the intake motors into one group

using namespace vex;

int IDLE = 0;
int MOVING = 1;
int kP = 5;
int TOLERANCE = 10;

int currentState = IDLE;
double leftEncoder = Left.rotation(degrees);
double rightEncoder = Right.rotation(degrees);
double leftError;
double rightError;
double leftVelocity;
double rightVelocity;
double highStop;
double lowStop;

void updateState(double destination) {
  leftEncoder = Left.rotation(degrees);
  rightEncoder = Right.rotation(degrees);

  highStop = destination + TOLERANCE;
  lowStop = destination - TOLERANCE;

  leftError = destination - leftEncoder;
  rightError = destination - rightEncoder;
}

int evaluateState() {
  if (currentState == IDLE) {
    return IDLE;
  }
  else {
    if(leftError > lowStop && leftError < highStop && rightError < highStop && rightError > lowStop) {
      return IDLE;
    }

    return MOVING;
  }
}

void reactToState() {
  leftVelocity = leftError / kP;
  rightVelocity = rightError / kP;
}

void auton(double destination) {
  updateState(destination);
  reactToState();
  currentState = evaluateState();
}