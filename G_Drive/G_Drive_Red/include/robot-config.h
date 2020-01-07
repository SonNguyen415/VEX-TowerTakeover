using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Arm;
extern motor IntakeLeft;
extern motor IntakeRight;
extern motor Tilter;
extern motor BackLeft;
extern motor FrontLeft;
extern motor FrontRight;
extern motor BackRight;
extern controller Controller1;
extern gyro Gyro;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );