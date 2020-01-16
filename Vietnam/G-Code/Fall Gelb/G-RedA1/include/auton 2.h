#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

motor_group Intake = motor_group(I1, I2);
motor_group Left = motor_group(L1, L2);
motor_group Right = motor_group(R1, R2);

bool GOING_UP = true;

const double TILTER_SETPOINT = 100;
const double TILTER_VELOCITY = 30;
const double kP = 4;
const int TOLERANCE = 5;
const double MAX_ARM_VELOCITY = 50;


//This function constrain constrainedValue between max and min
double constrain(double constrainedValue, double max, double min) {
  if(constrainedValue > max) {
    return max;
  } 
  if(constrainedValue < min) {
    return min;
  }
  return constrainedValue;
}


void move_arm(float setPoint) {

  while(true) {
    float error = setPoint - Arm.rotation(degrees);
    float armVelocity = error / kP;

    armVelocity = constrain(armVelocity, MAX_ARM_VELOCITY, -MAX_ARM_VELOCITY);
    
    if (GOING_UP) {
      Tilter.rotateTo(TILTER_SETPOINT, rotationUnits::deg, TILTER_VELOCITY, velocityUnits::pct, false);
    } else {
      Tilter.rotateTo(0, rotationUnits::deg, TILTER_VELOCITY, velocityUnits::pct, false);
    }

    Arm.spin(forward, armVelocity, percent);

    if(error > -TOLERANCE && error < TOLERANCE){
      break;
    }
    Controller.Screen.print("one sec Process complete");
    wait(1, seconds);
    Arm.stop(hold);
    return;
  }
}

void arms_to_bottom() {
  GOING_UP = false;
  move_arm(0);
}

void arms_to_middle() {
  GOING_UP = true;
  move_arm(200);
}

void arms_to_high() {
  GOING_UP = true;
  move_arm(400);
}


const double MAX_VELOCITY = 1;
const double MIN_VELOCITY = 0.1;

double speedMod = 0.5;

void faster() {
  speedMod += MIN_VELOCITY;
  if (speedMod > MAX_VELOCITY) {
    speedMod = MAX_VELOCITY;
  }
}

void slower() {
  speedMod -= MIN_VELOCITY;
  if (speedMod < MIN_VELOCITY) {
    speedMod = MIN_VELOCITY;
  }
}



//This function drive the PID to a destination at specified velocity)
void move (double leftSetPoint, double rightSetPoint, double maxLeft, double maxRight) {
  int TOLERANCE = 2;
  
  double kP = 5;
  double kI = 8;
  double kD = 10;

  double oldLeft = 0;
  double oldRight = 0;

  double totalLeft = 0;
  double totalRight = 0;

  while(1) {
    double leftEncoder = (L1.rotation(deg) + L2.rotation(deg)) / 2;
    double rightEncoder = (R1.rotation(deg) + R2.rotation(deg)) / 2;

    double leftError = leftSetPoint - leftEncoder;
    double rightError = rightSetPoint - rightEncoder;

    double leftChange = oldLeft - leftError;
    double rightChange = oldRight - rightError;

    totalLeft += leftError;
    totalRight += rightError;

    double leftVelocity = leftError / kP + totalLeft / kI - leftChange / kD;
    double rightVelocity = rightError / kP + totalRight / kI - rightChange / kD;

    leftVelocity = constrain(leftVelocity, maxLeft, -maxLeft);
    rightVelocity = constrain(leftVelocity, maxRight, -maxRight);

    Left.spin(forward, leftVelocity, percent);
    Right.spin(forward, rightVelocity, percent);

    oldLeft = leftError;
    oldRight = rightError;

    if (leftError < TOLERANCE && leftError > -TOLERANCE && rightError < TOLERANCE && rightError > -TOLERANCE) {
      break;
    }
  }
  return;
}

//This function rotate the intake to eat the cubes
void eat_cube(double rotationDegrees, bool completionWait) {
  Intake.rotateTo(rotationDegrees, rotationUnits::deg, 100, velocityUnits::pct, completionWait);
  return;
}

//This function turn the tilter to score cubes in goals
void score() {
  Tilter.rotateTo(200, rotationUnits::deg, 50, velocityUnits::pct);
}

