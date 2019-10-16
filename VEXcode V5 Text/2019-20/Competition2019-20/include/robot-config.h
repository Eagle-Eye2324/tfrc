using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LRDrive;
extern motor RRDrive;
extern motor LFDrive;
extern motor RFDrive;
extern controller Controller1;
extern motor armExtMotor;
extern motor armUpMotor1;
extern motor clawMotor;
extern motor armUpMotor2;
extern controller Controller2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );