using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LRDrive;
extern motor RRDrive;
extern motor LFDrive;
extern motor RFDrive;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );