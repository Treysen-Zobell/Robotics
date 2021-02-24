#include "vex.h"

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
// FrontRightDrive      motor         19              
// FrontLeftDrive       motor         11              
// Distance14           distance      14              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "Utils.h"
#include "MoveThread.h"
#include "Move.h"

using namespace vex;
competition Competition;
#define INVERT_TURNS 1 // 1 if left side, -1 if right
#define VISION_BALL Vision6__R_BALL // Vision6__R_BALL if red, Vision6__B_BALL if blue
#define CORNER_ONLY false
#define MODE 2 // 0 for homerow, 1 for one or two towers, 2 for skills, 4 for testing
#define TURN_SPEED 0.65
#define SLOW_TURN_SPEED 0.20
#define DRIVE_SPEED 0.80

// Captains Log, Oil Dirt Date 2-13-2021
// All systems nominal. We have recently defeated the traitorous ferengi, unfortunately we have been forced to team up with them at the admiral's command.

int driveX;
int driveY;
int ldrive; 
int rdrive;
int motorDir;
int motorDist;
int startPosition;
int blueSize;
int redSize;


void multipleColor()
{
  // Senses for largest object, color independent
  Vision6.takeSnapshot(Vision6__B_BALL);
  blueSize = Vision6.largestObject.height * Vision6.largestObject.width;
  Vision6.takeSnapshot(Vision6__R_BALL);
  redSize =  Vision6.largestObject.height * Vision6.largestObject.width;
  if(blueSize > redSize)
  {
    Vision6.takeSnapshot(Vision6__B_BALL);
  }
}

void driveSpeed(int speedliness)
{
  RearLeftDrive.setVelocity(speedliness, pct);
  FrontLeftDrive.setVelocity(speedliness, pct);
  RearRightDrive.setVelocity(speedliness, pct);
  FrontRightDrive.setVelocity(speedliness, pct);
}
// Centers the detected object
void SensorControl(double visionScale, int driveDist, int driveSpeed, bool auton)
{ 
 if(auton == true)
 {
  // Initial speed
  startPosition = RearLeftDrive.rotation(degrees);
  if(driveDist < 0)
  {
     while(RearLeftDrive.rotation(degrees) > startPosition + driveDist)
  {
      ldrive = -driveSpeed;
      rdrive = -driveSpeed;
  //Vision6.takeSnapshot(VISION_BALL);
  multipleColor();
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
  multipleColor();
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
   if(Vision6.largestObject.centerX > 100 && Vision6.largestObject.centerX < 200)
  {
    driveX += (Vision6.largestObject.centerX - 150) / visionScale;
    ldrive += driveX;
    rdrive -= driveX;
  }
 }
}

void setIntakeSpeed(int speed)
{
  LeftIntake.spin(forward, speed, pct);
  RightIntake.spin(forward, speed, pct);
}

void setLiftSpeed(int speed)
{
  LeftLift.spin(forward, speed, pct);
  RightLift.spin(forward, speed,pct);
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

void motorCheck()
{
  while(RearLeftDrive.isDone() == false || FrontLeftDrive.isDone() == false || RearRightDrive.isDone() == false || FrontRightDrive.isDone() == false)
  {
    wait(10, msec);
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
  driveSpeed(60);
  if(MODE == 2) //skills  //////////////////////////////////////////////////////////////////////////////////////
  {

  //Turns and deposits preload into goal, turns to face ball
  Move::moveDeg(20);
  setLiftSpeed(100);
  wait(400, msec);
  setLiftSpeed(0);
  Move::moveDeg(10);

  //Moves Forward and grabs first ball
  //SimpleMove::moveMM(300);
  setIntakeSpeed(100);
  SensorControl(3.5, 500, 50, true);
  //Utils::brake();
  //driveSpeed(50); Move::moveDeg(-10);
  //Utils::brake();
  SensorControl(4, 600, 50, true);
  setIntakeSpeed(0);
  Utils::brake();

  //Turns to face away from corner goal, backs up to goal
  driveSpeed(50); Move::moveDeg(100);
  Utils::brake();
  setIntakeSpeed(100);
  setLiftSpeed(100);
  SensorControl(3, -350, 80, true);

  //Deposits ball
  wait(1700, msec);
  setLiftSpeed(0);

  //Moves forward and grabs ball on the center line
  Move::moveMM(200);
  Utils::brake();
  Move::moveDeg(-35);
  Utils::brake();
  SensorControl(4, 1350, 80, true);
  Utils::brake();

  //Turns away from side goal, deposits ball 
  Move::moveDeg(90);
  Utils::brake();
  setLiftSpeed(100);
  SensorControl(4, -150, 80, true);
  Utils::brake();
  wait(1500, msec);
  setLiftSpeed(0);

  //uses vision to line up, grabs other ball
  SensorControl(3.5, 450, 50, true);
  Utils::brake();

  // Turns and grabs ball near corner goal
  Move::moveMM(200);
  Utils::brake();
  Move::moveDeg(-90);
  Utils::brake();
  SensorControl(4, 1400, 70, true);
  Utils::brake();

  // Backs up, turns away from corner goal, backs up using vision
  Move::moveMM(-650);
  Utils::brake();
  Move::moveDeg(145);
  Utils::brake();
  setLiftSpeed(50);
  SensorControl(4, -700, 70, true);
  Utils::brake();
  setIntakeSpeed(0);
  setLiftSpeed(100);
  wait(1500, msec);
  setLiftSpeed(0);

  //Moves away from goal, turns toward ball and grabs it
  Move::moveMM(250);
  Utils::brake();
  //Move::moveDeg(-15);
  Utils::brake();
  setIntakeSpeed(100);
  SensorControl(4, 1575, 80, true);

  //Turns away from side goal, backs up to it using vision
  Move::moveDeg(85);
  Utils::brake();
  SensorControl(4, -700, 70, true);
  setLiftSpeed(100);
  wait(1000, msec);

  }
  if(MODE == 0) // Homerow auton //////////////////////////////////////////////////////
  {

  //SimpleMove Back
  Move::moveMM(-250);
  Utils::brake();

  // Turn to face goal
  Move::moveDeg(45 * INVERT_TURNS);

  // Move Forward and grab ball
  setIntakeSpeed(100);
  //setLiftSpeed(100);
  SensorControl(3, 200, 80, true);
  Utils::brake();
  //SimpleMove::moveMM(200);

  // 5. Reverse from goal, turn sideways, move forward 
  setIntakeSpeed(0);
  driveSpeed(80); Move::moveMM(-225);
  Utils::brake();
  Move::moveDeg(60);
  Utils::brake();
  Move::moveMM(150);

  // Turn to face away from goal, back up using vision
  Move::moveDeg(100);
  SensorControl(3.5, -300, 75, true);
  Utils::brake();
  wait(400, msec);

  //Deposit payload
  setLiftSpeed(100);
  wait(500, msec);
  setLiftSpeed(0);

  //Move Forward, turn towards center
  Move::moveMM(500);
  Move::moveDeg(45 * INVERT_TURNS);

  //Move to center goal, turn to face away from goal
  driveSpeed(90); Move::moveMM(1200);
  Move::moveDeg(-85 * INVERT_TURNS);
  Utils::brake();

  //reverse to goal, deposit ball
  setLiftSpeed(80);
  setIntakeSpeed(80);
  //SimpleMove::moveMM(-375);
  SensorControl(3.5, -150, 70, true);
  Utils::brake();
  setLiftSpeed(100);
  setIntakeSpeed(100);
  wait(1300, msec);
  setLiftSpeed(0);
  setIntakeSpeed(0);

  //SimpleMove forward, turn towards corner goal
  Move::moveMM(400);
  Move::moveDeg(90 * INVERT_TURNS);
  Utils::brake();

  //SimpleMove to corner goal, turn towards it
  Move::moveMM(950);
  Utils::brake();
  Move::moveDeg(50 * INVERT_TURNS);
  Utils::brake();

  //Approach using active vision
  setIntakeSpeed(100);
  /*
  float leftEndPosition = LeftDrive.rotation(deg) + 600;
    while (LeftDrive.rotation(deg) < leftEndPosition)
    {
      Vision6.takeSnapshot(VISION_BALL);
      // Initial speed
      driveX = 0;
      ldrive = 80;
      rdrive = 80;
      SensorControl(4);

      // Update motor speeds
      LeftDrive.spin(fwd, ldrive, pct);
      FrontLeftDrive.spin(fwd, ldrive, pct);
      RightDrive.spin(fwd, rdrive, pct);
      FrontRightDrive.spin(fwd, rdrive, pct);
    }
    */
  SensorControl(3, 400, 80, true);

  // Reverse, turn 180 degrees, reverse to goal
  Move::moveMM(-160);
  Utils::brake();
  Move::moveDeg(170);
  Utils::brake();
  Move::moveMM(-265);
  Utils::brake();

  //Deposit Ball
  setLiftSpeed(100);
  //End of homerow autonomous
  }

if(MODE == 1) // One/two tower auton  ///////////////////////////////////////////////////
{
  // 1. Turn
  Move::moveDeg(20 * INVERT_TURNS);

  // 2. Deposit preload
  setIntakeSpeed(100);
  setLiftSpeed(100);

  wait(1000, msec);

  Move::moveDeg(25 * INVERT_TURNS);

  setIntakeSpeed(0);
  setLiftSpeed(0);

  if (!CORNER_ONLY)
  {
    // 3. SimpleMove away from goal and turn to face other goal
    Move::moveMM(900);
    Move::moveDeg(-80 * INVERT_TURNS);

    // 4. Approach, correcting using active vision
    setIntakeSpeed(100);
    //float rightEndPosition = RightDrive.rotation(deg) + 600;
    SensorControl(3, 600, 80, true);
    /*
    float leftEndPosition = LeftDrive.rotation(deg) + 600;
    while (LeftDrive.rotation(deg) < leftEndPosition)
    {
      Vision6.takeSnapshot(VISION_BALL);
      // Initial speed
      driveX = 0;
      ldrive = 80;
      rdrive = 80;
      SensorControl(4);

      // Update motor speeds
      LeftDrive.spin(fwd, ldrive, pct);
      FrontLeftDrive.spin(fwd, ldrive, pct);
      RightDrive.spin(fwd, rdrive, pct);
      FrontRightDrive.spin(fwd, rdrive, pct);
    }
    */
    Utils::brake();

    // 5. Reverse from goal, turn 180deg, reverse to goal
  setIntakeSpeed(0);
  driveSpeed(80);
  Move::moveMM(-250);
  Utils::brake();
  Move::moveDeg(190);
  Utils::brake();
  Move::moveMM(-275);


    // 6. Eject payload
    setLiftSpeed(100);
    setIntakeSpeed(100);
  }
}

/*
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
  // RightDrive.spin(forward, 80 * INVERT_TURNS, pct);
  // LeftDrive.spin(forward, 45 * INVERT_TURNS, pct);
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
  for(int i = 0; i < 50; i++)
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
  LeftDrive.spin(reverse, 80, pct);
  RightDrive.spin(reverse, 80, pct);

  wait(390, msec);

  // turn right
  LeftDrive.spin(forward, 80 * INVERT_TURNS, pct);
  RightDrive.spin(reverse, 80 * INVERT_TURNS, pct);

  wait(750, msec);

  // stop
  LeftDrive.spin(forward, 0, pct);
  RightDrive.spin(forward, 0, pct);

  wait(100, msec);

  // reverse
  RightDrive.spin(reverse, 80, pct);
  LeftDrive.spin(reverse, 80, pct);

  wait(700, msec);

  // stop
  LeftDrive.spin(forward, 0, pct);
  RightDrive.spin(forward, 0, pct);

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
  RightDrive.spin(forward, 80, pct);
  LeftDrive.spin(forward, 80, pct);

  wait(200, msec);

  // stop
  LeftDrive.spin(forward, 0, pct);
  RightDrive.spin(forward, 0, pct);
  

   
  Vision Example
    for(int i = 0; i < 123; i++)
    {
      ldrive = 35;
      rdrive = 35;
      Vision6.takeSnapshot(Vision6__R_BALL);
      if(Vision6.largestObject.centerX < 140)
      {
        ldrive -= 5;
        rdrive += 5;
      }
      else if(Vision6.largestObject.centerX > 170)
      {
        ldrive += 5;
        rdrive -= 5;
      }
      LeftDrive.spin(forward, ldrive, pct);
      RightDrive.spin(forward, rdrive, pct);
      wait(10, msec);
    }
    */

}

//User Control Function(s):
void usercontrol(void)
{
  while(true)
  { 
    if(Controller1.ButtonDown.pressing())
    {
      for(int n = 0; n < 1; n++)
      {
         RearLeftDrive.spin(forward, 100, pct);
         RearRightDrive.spin(reverse, 100, pct);
         FrontLeftDrive.spin(forward, 100, pct);
         FrontRightDrive.spin(reverse, 100, pct);
         wait(750, msec);
         RearLeftDrive.setStopping(brake);
         RearRightDrive.setStopping(brake);
         FrontLeftDrive.setStopping(brake);
         FrontRightDrive.setStopping(brake);
         // SimpleMove::moveDeg(180, LeftDrive, FrontLeftDrive, RightDrive, FrontRightDrive);
      }
    }
    driveX = TURN_SPEED * Controller1.Axis1.position();
    driveX += SLOW_TURN_SPEED * Controller1.Axis4.position();
    driveY = DRIVE_SPEED * Controller1.Axis3.position();

    //Vision6.takeSnapshot(VISION_BALL);
    
    if((Distance14.objectDistance(mm) > 350 or Distance14.objectDistance(mm) == 0) && driveY >= 0)
    {
      multipleColor();
      SensorControl(4.5, 0, 0, false);
    }
    else
    {
      if(Controller1.Axis3.position() < 50)
      {
        driveY = .5 * driveY;
      }
      if(Controller1.Axis1.position() < 50)
      {
      driveX = .5 * driveX;
      }
    }

    RearLeftDrive.spin(forward, driveY + driveX, pct);
    RearRightDrive.spin(forward, driveY - driveX, pct);
    FrontLeftDrive.spin(forward, driveY + driveX, pct);
    FrontRightDrive.spin(forward, driveY - driveX, pct);
    chainControl();
    Controller1.Screen.clearScreen();
    Controller1.Screen.print("Distance: ");
    Controller1.Screen.print(Distance14.objectDistance(mm));
    Controller1.Screen.newLine();

    wait(5, msec);
  }
}

// Main Function:
int main() 
{
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
}