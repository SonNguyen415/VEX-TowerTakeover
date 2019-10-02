#include "user.cpp"

const int PROPORTION_CONSTANT = 6;
const int DERIVATIVE_CONSTANT = 8;
const int INTEGRAL_CONSTANT = 20;
const float MIN_VELOCITY_PERCENTAGE = 1;

void Move(float leftDestination, float rightDestination, float maxVelocity) {
  //First we must reset the motors rotation values to start at 0
  Reset();

  /* Initialize the previous velocities of the motors first as the maximum velocity, 
   * which is also to the starting current velocities. This will allow us to measure 
   * the deceleration of the motors later on.
   */
  float previousLeft = maxVelocity;
  float previousRight = maxVelocity;

  // Initialize the change in velocity of each side to measure the deceleration of the motors.
  float leftChange = 0;
  float rightChange = 0;
  
  /* Initialize the total accumulated errors between the desired destination and the
   * current rotation so we can prevent steady-state errors.
   */
  float totalRight = 0;
  float totalLeft = 0;
    
  while(1) {
    //Assign the current rotations of each motor to separate variables
    float leftFrontEncoder = LeftFront.rotation(rotationUnits::deg);
    float leftBackEncoder = LeftBack.rotation(rotationUnits::deg);
    float rightFrontEncoder = RightFront.rotation(rotationUnits::deg);
    float rightBackEncoder = RightBack.rotation(rotationUnits::deg);
    
    //Measure the average rotation values between the front and back motors of each side
    float leftRotation = (leftFrontEncoder + leftBackEncoder) / 2;
    float rightRotation = (rightFrontEncoder + rightBackEncoder) / 2;
    
    //Calculate the difference between the desired destination and the current rotation
    float rightError = rightDestination - rightRotation;
    float leftError = leftDestination - leftRotation;
    
    //The error is now used as the velocity, as error decreases, velocity decreases
    //The accumulated error is added in to make sure the robot is not going too slow
    //The change in error is subtracted to make sure the robot is not going too fast
    float rightVelocity = rightError / PROPORTION_CONSTANT + totalRight / INTEGRAL_CONSTANT - rightChange / DERIVATIVE_CONSTANT;
    float leftVelocity = leftError / PROPORTION_CONSTANT + totalLeft / INTEGRAL_CONSTANT - leftChange / DERIVATIVE_CONSTANT;
    
    //Constrains the velocity of the motors to the specified maximum velocity
    rightVelocity = Constrain(rightVelocity, maxVelocity, -maxVelocity);
    leftVelocity = Constrain(leftVelocity, maxVelocity, -maxVelocity);
    
    //Here we calculate the change in velocity
    leftChange = previousLeft - leftVelocity;
    rightChange = previousRight - rightVelocity;
    
    /* Now we set the previous velocity to equal to the current velocity, so when the loop
     * goes through again we will have a differnt velocity
     */
    previousLeft = leftVelocity;
    previousRight = rightVelocity;
    
    //Here we calculate the total accumulated errors
    totalLeft += leftError;
    totalRight += rightError;
    
    //Set the motors velocity to equal to the outputed velocity
    LeftFront.setVelocity(leftVelocity,velocityUnits::pct);
    LeftBack.setVelocity(leftVelocity,velocityUnits::pct);
    RightFront.setVelocity(rightVelocity,velocityUnits::pct);
    RightBack.setVelocity(rightVelocity,velocityUnits::pct);
      
    //Tell the motors to spin so it'll actually run
    LeftFront.spin(directionType::fwd);
    RightFront.spin(directionType::fwd);
    LeftBack.spin(directionType::fwd);
    RightBack.spin(directionType::fwd);
    
    //Used for debugging
    Brain.Screen.printAt(1, 40, "%6.1f", leftVelocity);
    Brain.Screen.printAt(1, 80, "%6.1f", rightVelocity);
    Controller.Screen.print(leftVelocity);      
    
    //Stop the robot if the velocity of each side is between 1 and -1
    if(leftVelocity <= MIN_VELOCITY_PERCENTAGE && leftVelocity >= -MIN_VELOCITY_PERCENTAGE && 
      rightVelocity <= MIN_VELOCITY_PERCENTAGE && leftVelocity >= -MIN_VELOCITY_PERCENTAGE ) {
      break;
    }else {
      task::sleep(10);
    }
  }
  return;
}


/*States:
1. Rest
2. 
*/