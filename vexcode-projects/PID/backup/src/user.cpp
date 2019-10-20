#include "config.cpp"

const float LIFT_VELOCITY = 50;
const float SPEED_MODIFIER_INCREMENT= 0.25;
const float MIN_VELOCITY_DECIMAL = 0.1;
const float MAX_VELOCITY_DECIMAL  = 0.1;

float speed_modifier = 0.5;

//constrain value to between maxValue and minValue
float Constrain(float value, float maxValue, float minValue) {
  if(value >= maxValue) {
    value = maxValue;
  }
  if(value <= minValue) {
    value = minValue;
  }
  return value;
}

//Increase the speed modifier each time this function is called to make it goes faster
void Faster() {
  speed_modifier = speed_modifier + SPEED_MODIFIER_INCREMENT;
  speed_modifier = Constrain(speed_modifier, MIN_VELOCITY_DECIMAL, MAX_VELOCITY_DECIMAL);
}

//Decrease the speed modifier each time this function is called to make it goes slower
void Slower() {
  speed_modifier = speed_modifier - SPEED_MODIFIER_INCREMENT;
  speed_modifier = Constrain(speed_modifier, MIN_VELOCITY_DECIMAL, MAX_VELOCITY_DECIMAL);
}

//Reset the current rotation of the motors to 0
void Reset() {
  LeftFront.resetRotation();
  LeftBack.resetRotation();
  RightFront.resetRotation();
  RightBack.resetRotation();
}

//Raise the arm whenever this function is called
void RaiseArm() {
  LiftMotor.spin(directionType::fwd, LIFT_VELOCITY, velocityUnits::pct);
}

//Lower the arm whenever this function is called
void LowerArm() {
  LiftMotor.spin(directionType::rev, LIFT_VELOCITY, velocityUnits::pct);
}

//Stop the arm whenever this function is called
void StopArm() {
  LiftMotor.stop(brakeType::hold);
}

void Forward() {
  Motor1.spin(directionType::fwd, 10, velocityUnits::pct);
  Motor2.spin(directionType::fwd, 10, velocityUnits::pct);
}

void Backward() {
  Motor1.spin(directionType::rev, 10, velocityUnits::pct);
  Motor2.spin(directionType::rev, 10, velocityUnits::pct);
}