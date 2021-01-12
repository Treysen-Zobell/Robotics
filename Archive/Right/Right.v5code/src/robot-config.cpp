#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor lift1 = motor(PORT9, ratio18_1, true);
motor backright = motor(PORT10, ratio18_1, true);
motor intake1 = motor(PORT8, ratio18_1, false);
motor intake2 = motor(PORT3, ratio18_1, false);
motor lift2 = motor(PORT5, ratio18_1, false);
motor backleft = motor(PORT1, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}