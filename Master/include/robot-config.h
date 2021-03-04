using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor RearLeftDrive;
extern motor RearRightDrive;
extern motor RightIntake;
extern motor LeftIntake;
extern motor RightLift;
extern motor LeftLift;
extern signature Vision6__B_BALL;
extern signature Vision6__R_BALL;
extern signature Vision6__SIG_3;
extern signature Vision6__SIG_4;
extern signature Vision6__SIG_5;
extern signature Vision6__SIG_6;
extern signature Vision6__SIG_7;
extern vision Vision6;
extern motor BarMotor;
extern motor FrontRightDrive;
extern motor FrontLeftDrive;
extern distance Distance14;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );