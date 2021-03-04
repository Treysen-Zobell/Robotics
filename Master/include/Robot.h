#include <vex.h>

struct Robot
{
  // vars
  static int leftDriveSpeed;
  static int rightDriveSpeed;
  
  // utils
  static void setDriveSpeed(int speed);
  static void driveForward(int distance, unsigned int speed, bool auton, bool aimAssist, float visionScale, unsigned int color);
  static void setIntakeSpeed(int speed);
  static void setLiftSpeed(int speed);
  static void brake();
  
  // driver control based
  static void chainControl();
};
