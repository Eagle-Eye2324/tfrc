#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LRDrive = motor(PORT1, ratio18_1, true);
motor RRDrive = motor(PORT10, ratio18_1, false);
motor LFDrive = motor(PORT11, ratio18_1, true);
motor RFDrive = motor(PORT20, ratio18_1, false);
controller Controller1 = controller(primary);
motor armExtMotor = motor(PORT4, ratio18_1, true);
motor armUpMotor1 = motor(PORT3, ratio18_1, false);
motor clawMotor = motor(PORT15, ratio18_1, false);
motor armUpMotor2 = motor(PORT5, ratio18_1, true);
controller Controller2 = controller(partner);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}