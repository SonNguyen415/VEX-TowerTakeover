using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor R;
extern motor L;
extern motor M1;
extern motor M2;
extern motor Grip;
extern gyro Gyro;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );