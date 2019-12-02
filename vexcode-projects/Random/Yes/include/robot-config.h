using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Intake1;
extern motor Intake2;
extern motor R1;
extern motor R2;
extern motor L1;
extern motor L2;
extern motor Lift;
extern motor Tilter;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );