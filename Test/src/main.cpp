// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDrive            motor         1               
// RightDrive           motor         10              
// RightIntake          motor         8               
// LeftIntake           motor         2               
// RightLift            motor         9               
// LeftLift             motor         3               
// Vision6              vision        6               
// BarMotor             motor         4               
// LeftDrive2           motor         21              
// RightDrive2          motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDrive            motor         1               
// RightDrive           motor         10              
// RightIntake          motor         8               
// LeftIntake           motor         2               
// RightLift            motor         9               
// LeftLift             motor         3               
// Vision6              vision        6               
// BarMotor             motor         4               
// LeftDrive2           motor         21              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

#include "Move.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDrive            motor         1               
// RightDrive           motor         10              
// RightIntake          motor         8               
// LeftIntake           motor         2               
// RightLift            motor         9               
// LeftLift             motor         3               
// Vision6              vision        6               
// BarMotor             motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include <cmath>

#define INVERT_TURNS -1 // 1 if left side, -1 if right
#define VISION_BALL Vision6__B_BALL // Vision6__R_BALL if red, Vision6__B_BALL if blue

using namespace vex;
competition Competition;

int AmmonX;
int driveX;
int driveY;
int ldrive;
int rdrive;

void maxVal()
{
 if ((driveY + driveX) > 100)
 {
   driveY = (driveY / ((driveX + driveY) / 100));
 }
}

void SensorControl()
{
  if (driveX < 5 && driveX > -5)
  {
    if(Vision6.largestObject.centerX < 140 && Vision6.largestObject.centerX > 120)
    {
      driveX += -5;
    }
    else if (Vision6.largestObject.centerX <= 120 && Vision6.largestObject.centerX > 80)
    {
      driveX += -10;
    }
    else if(Vision6.largestObject.centerX > 160 && Vision6.largestObject.centerX < 180)
    {
      driveX += 5;
    }
    else if (Vision6.largestObject.centerX >= 180 && Vision6.largestObject.centerX < 210)
    {
      driveX += 10; 
    }
  }
}

void chainControl()
{
  // Lift and Feed Controls
  if(Controller1.ButtonL1.pressing())
  {
    LeftIntake.spin(forward, 100, pct);
    LeftLift.spin(forward, 100, pct);
    RightIntake.spin(forward, 100, pct);
    RightLift.spin(forward, 100, pct);
  }
  else if(Controller1.ButtonL2.pressing())
  {
    LeftIntake.spin(reverse, 100, pct);
    LeftLift.spin(reverse, 100, pct);
    RightIntake.spin(reverse, 100, pct);
    RightLift.spin(reverse, 100, pct);
  }
  else if(Controller1.ButtonR1.pressing())
  {
    LeftIntake.spin(forward, 100, pct);
    LeftLift.spin(forward, 0, pct);
    RightIntake.spin(forward, 100, pct);
    RightLift.spin(forward, 0, pct);
  }
  else if(Controller1.ButtonR2.pressing())
  {
    LeftIntake.spin(reverse, 100, pct);
    LeftLift.spin(forward, 0, pct);
    RightIntake.spin(reverse, 100, pct);
    RightLift.spin(forward, 0, pct);
  }
  else
  {
    LeftIntake.spin(forward, 0, pct);
    LeftLift.spin(forward, 0, pct);
    RightIntake.spin(forward, 0, pct);
    RightLift.spin(forward, 0, pct);
  }

  // Flippery Guy
  if(Controller1.ButtonA.pressing())
  {
    BarMotor.spin(forward, 100, pct);
  }
  else if (Controller1.ButtonB.pressing())
  {
    BarMotor.spin(reverse, 100, pct);
  }
  else
  {
    BarMotor.spin(forward, 0, pct);
  }
}

// Beginning of match functions
void pre_auton(void)
{
  vexcodeInit();
}

  //Autonomous Function(s):
void autonomous(void)
{
  
 // dump preload into center goal

 
  // turn right
  RightDrive.spin(reverse, 100 * INVERT_TURNS, pct);
  LeftDrive.spin(forward, 100 * INVERT_TURNS, pct);
  
  wait(140, msec);

  // stop
  RightDrive.spin(reverse, 0, pct);
  LeftDrive.spin(forward, 0, pct);

  // start intakes
  LeftIntake.spin(forward, 100, pct);
  RightIntake.spin(forward, 100, pct);
  LeftLift.spin(forward, 100, pct);
  RightLift.spin(forward, 100,pct);

  wait(1000, msec);

  // stop intakes  
  LeftIntake.spin(forward, 0, pct);
  RightIntake.spin(forward, 0, pct);
  LeftLift.spin(forward, 0, pct);
  RightLift.spin(forward, 0, pct);

  // turn right 
  LeftDrive.spin(forward, 80 * INVERT_TURNS, pct);
  RightDrive.spin(reverse, 80 * INVERT_TURNS, pct);

  wait(400, msec);

  // arc to corner and engage intakes
  RightDrive.spin(forward, 62.5 + (17.5 * INVERT_TURNS), pct);
  LeftDrive.spin(forward, 62.5 - (17.5 * INVERT_TURNS), pct);
  LeftIntake.spin(forward, 80, pct);
  RightIntake.spin(forward, 80, pct);

  wait(2100, msec);

  // engage intake and lift
  LeftIntake.spin(forward, 80, pct);
  RightIntake.spin(forward, 80, pct);
  LeftLift.spin(forward, 80, pct);
  RightLift.spin(forward, 80, pct);

  // vision sensor corrections
  for(int i = 0; i< 50; i++)
  {
    ldrive = 40;
    rdrive = 20;
    Vision6.takeSnapshot(VISION_BALL);
    if(Vision6.largestObject.centerX > 170)
    {
      ldrive += 15;
      rdrive -= 15;
    }
    else if(Vision6.largestObject.centerX < 140)
    {
      ldrive -= 15;
      rdrive += 15;
    }
      LeftDrive.spin(forward, ldrive, pct);
      RightDrive.spin(forward, rdrive, pct);
      wait(10, msec);
  }
      

  // lift and intake stop
  RightIntake.spin(forward, 0, pct);
  LeftIntake.spin(forward, 0, pct);
  LeftLift.spin(forward, 0, pct);
  RightLift.spin(forward, 0, pct);

  // reverse
  Move::moveMM(-300, LeftDrive, LeftDrive2, RightDrive, RightDrive2);

  // turn right
  Move::moveDeg(90 * INVERT_TURNS, LeftDrive, LeftDrive2, RightDrive, RightDrive2);

  wait(100, msec);
  
  // reverse
  Move::moveMM(-300, LeftDrive, LeftDrive2, RightDrive, RightDrive2);

  //dump ball into corner goal
  
  // engage intake and lift
  LeftIntake.spin(forward, 80, pct);
  RightIntake.spin(forward, 80, pct);
  LeftLift.spin(forward, 80, pct);
  RightLift.spin(forward, 80, pct);

  wait(3100, msec);
    
  // stop intake and lift
  RightIntake.spin(forward, 0, pct);
  LeftIntake.spin(forward, 0, pct);
  LeftLift.spin(forward, 0, pct);
  RightLift.spin(forward, 0, pct);

  // forward
  Move::moveMM(100, LeftDrive, LeftDrive2, RightDrive, RightDrive2);
}

//User Control Function(s):
void usercontrol(void)
{
  while(true)
  {
    Vision6.takeSnapshot(Vision6__R_BALL);

    driveX = 0.85 * Controller1.Axis1.position();
    driveY = 0.85 *Controller1.Axis3.position();
    SensorControl();

    LeftDrive.spin(forward, driveY + driveX, pct);
    RightDrive.spin(forward, driveY - driveX, pct);

    chainControl();
    if(Controller1.ButtonA.pressing() or Controller1.ButtonB.pressing())
    {
      if(Controller1.Axis1.position() < 5 && Controller1.Axis1.position() >-5 && Controller1.Axis3.position() < 5 && Controller1.Axis3.position() >-5)
      {
        //Wheels lock
        
      }
    }
  }
}

// Main Function:
int main() 
{
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
}
