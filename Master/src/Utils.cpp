#include "Utils.h"
#include "vex.h"
//#include "robot-config.h"

void Utils::brake()
{
  RearLeftDrive.setStopping(vex::brake);
  FrontLeftDrive.setStopping(vex::brake);
  RearRightDrive.setStopping(vex::brake);
  FrontRightDrive.setStopping(vex::brake);
  wait(20, msec);
}

void Utils::multipleColor()
{
  // Senses for largest object, color independent
  Vision6.takeSnapshot(Vision6__B_BALL);
  int blueSize = Vision6.largestObject.height * Vision6.largestObject.width;
  Vision6.takeSnapshot(Vision6__R_BALL);
  int redSize =  Vision6.largestObject.height * Vision6.largestObject.width;
  if(blueSize > redSize)
  {
    Vision6.takeSnapshot(Vision6__B_BALL);
  }
}

// Centers the detected object
void SensorControl(double visionScale, int driveDist, int driveSpeed, bool auton)
{
  if(auton == true)
  {
    // Initial speed
    float startPosition = RearLeftDrive.rotation(degrees);
    if(driveDist < 0)
    {
      while(RearLeftDrive.rotation(degrees) > startPosition + driveDist)
      {

        ldrive = -driveSpeed;
        rdrive = -driveSpeed;
        //Vision6.takeSnapshot(VISION_BALL);
        Utils::multipleColor();
        driveX = 0;

        if(Vision6.largestObject.centerX > 100 && Vision6.largestObject.centerX < 200)
        {
          driveX += (Vision6.largestObject.centerX - 150) / visionScale;
          ldrive += driveX;
          rdrive -= driveX;
        }

        // Update motor speeds
        RearLeftDrive.spin(fwd, ldrive, pct);
        FrontLeftDrive.spin(fwd, ldrive, pct);
        RearRightDrive.spin(fwd, rdrive, pct);
        FrontRightDrive.spin(fwd, rdrive, pct);
      }
    }

    else
    {
      while(RearLeftDrive.rotation(degrees) < startPosition + driveDist)
      {
        ldrive = driveSpeed;
        rdrive = driveSpeed;
        //Vision6.takeSnapshot(VISION_BALL);
        Utils::multipleColor();
        driveX = 0;

        if(Vision6.largestObject.centerX > 100 && Vision6.largestObject.centerX < 200)
        {
          driveX += (Vision6.largestObject.centerX - 150) / visionScale;
          ldrive += driveX;
          rdrive -= driveX;
        }

        // Update motor speeds
        RearLeftDrive.spin(fwd, ldrive, pct);
        FrontLeftDrive.spin(fwd, ldrive, pct);
        RearRightDrive.spin(fwd, rdrive, pct);
        FrontRightDrive.spin(fwd, rdrive, pct);
      }
    }
  }
 
  else
  {
    if (Vision6.largestObject.centerX > 100 && Vision6.largestObject.centerX < 200)
    {
      driveX += (Vision6.largestObject.centerX - 150) / visionScale;
      ldrive += driveX;
      rdrive -= driveX;
    }
  }
}