#include "Robot.h"
#include "Vision.h"

int Robot::leftDriveSpeed = 0;
int Robot::rightDriveSpeed = 0;

void Robot::setDriveSpeed(int speed)
{
  RearLeftDrive.setVelocity(speed, pct);
  FrontLeftDrive.setVelocity(speed, pct);
  RearRightDrive.setVelocity(speed, pct);
  FrontRightDrive.setVelocity(speed, pct);
}

void Robot::driveForward(int distance, unsigned int speed, bool auton, bool aimAssist, float visionScale, unsigned int color)
{
  if (auton)
  {
    int startPosition = RearLeftDrive.rotation(vex::degrees);
    int direction = (RearLeftDrive.rotation(degrees) > startPosition + distance) ? 1 : -1;

    // RearLeftDrive.rotation(degrees) -> current
    // startPosition                   -> start pos
    // distance                        -> distance to travel
    // direction                       -> 1 or -1 motor direction
    while((RearLeftDrive.rotation(degrees) - startPosition) * direction <= distance * direction)
    {
      Robot::leftDriveSpeed = speed * direction;
      Robot::rightDriveSpeed = speed * direction;

      if (aimAssist)
      {
        Vision::findLargest(color);

        if(Vision6.largestObject.centerX > 100 && Vision6.largestObject.centerX < 200)
        {
          int driveX = (Vision6.largestObject.centerX - 150) / visionScale;
          Robot::leftDriveSpeed += driveX;
          Robot::rightDriveSpeed -= driveX;
        }
      }

      RearLeftDrive.spin(vex::forward, Robot::leftDriveSpeed, vex::pct);
      FrontLeftDrive.spin(vex::forward, Robot::leftDriveSpeed, vex::pct);
      RearRightDrive.spin(vex::forward, Robot::rightDriveSpeed, vex::pct);
      FrontRightDrive.spin(vex::forward, Robot::rightDriveSpeed, vex::pct);
    }
  }

  else // driver control
  {
    if (aimAssist)
    {
      // applies on top of current movement inputs
      int driveX = (Vision6.largestObject.centerX - 150) / visionScale;
      Robot::leftDriveSpeed += driveX;
      Robot::rightDriveSpeed -= driveX;
    }
  }
}

void Robot::setIntakeSpeed(int speed)
{
  LeftIntake.spin(vex::forward, speed, vex::pct);
  RightIntake.spin(vex::forward, speed, vex::pct);
}

void Robot::setLiftSpeed(int speed)
{
  LeftLift.spin(vex::forward, speed, vex::pct);
  RightLift.spin(vex::forward, speed, vex::pct);
}

void Robot::brake()
{
  RearLeftDrive.setStopping(vex::brake);
  FrontLeftDrive.setStopping(vex::brake);
  RearRightDrive.setStopping(vex::brake);
  FrontRightDrive.setStopping(vex::brake);
}

void Robot::chainControl()
{
  if (Controller1.ButtonL1.pressing())
  {
    LeftIntake.spin(vex::forward, 100, vex::pct);
    LeftLift.spin(vex::forward, 100, vex::pct);
    RightIntake.spin(vex::forward, 100, vex::pct);
    RightLift.spin(vex::forward, 100, vex::pct);
  }
  else if (Controller1.ButtonL2.pressing())
  {
    LeftIntake.spin(vex::reverse, 100, vex::pct);
    LeftLift.spin(vex::reverse, 100, vex::pct);
    RightIntake.spin(vex::reverse, 100, vex::pct);
    RightLift.spin(vex::reverse, 100, vex::pct);
  }
  else if (Controller1.ButtonR1.pressing())
  {
    LeftIntake.spin(vex::forward, 100, vex::pct);
    LeftLift.spin(vex::forward, 0, vex::pct);
    RightIntake.spin(vex::forward, 100, vex::pct);
    RightLift.spin(vex::forward, 0, vex::pct);
  }
  else if (Controller1.ButtonR2.pressing())
  {
    LeftIntake.spin(vex::reverse, 100, vex::pct);
    LeftLift.spin(vex::forward, 0, vex::pct);
    RightIntake.spin(vex::reverse, 100, vex::pct);
    RightLift.spin(vex::forward, 0, vex::pct);
  }
  else
  {
    LeftIntake.spin(vex::forward, 0, vex::pct);
    LeftLift.spin(vex::forward, 0, vex::pct);
    RightIntake.spin(vex::forward, 0, vex::pct);
    RightLift.spin(vex::forward, 0, vex::pct);
  }

  // rear descoring bar
  if (Controller1.ButtonA.pressing()) { BarMotor.spin(vex::forward, 100, vex::pct); }
  else if (Controller1.ButtonB.pressing()) { BarMotor.spin(vex::reverse, 100, vex::pct); }
  else { BarMotor.spin(vex::forward, 0, vex::pct); }
}
