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

#include "MoveThread.h"
#include "Move.h"

#define INVERT_TURNS 1 // 1 if left side, -1 if right
#define VISION_BALL Vision6__B_BALL // Vision6__R_BALL if red, Vision6__B_BALL if blue
#define CORNER_ONLY false
#define SKILLZ true

using namespace vex;
competition Competition;

unsigned int AmmonX = 0x0000;
int driveX;
int driveY;
int ldrive;
int rdrive;
int blueSize;
int redSize;
int motorDir;
int motorDist;
double visionScale = 3;

// Centers the detected object
void SensorControl(double visionScale)
{
 if(Vision6.largestObject.centerX > 100 && Vision6.largestObject.centerX < 200)
 {
   driveX += (Vision6.largestObject.centerX - 150) / visionScale;
   ldrive += driveX;
   rdrive -= driveX;
 }
}

int spinLeft()
{
 LeftDrive.spinFor(reverse, motorDist, degrees);
  while(FrontLeftDrive.isDone() == false)
 {
   wait(10, msec);
 }
 return 0;
}

int spinFrontLeft()
{
 FrontLeftDrive.spinFor(reverse, motorDist, degrees);
 while(FrontLeftDrive.isDone() == false)
 {
   this_thread::sleep_for(25);
 }
 return 0;
}

int spinRight()
{
 RightDrive.spinFor(reverse, motorDist, degrees);
 while(RightDrive.isDone() == false)
 {
   this_thread::sleep_for(25);
 }
 return 0;
}

int spinFrontRight()
{
 FrontRightDrive.spinFor(reverse, motorDist, degrees);
 while(FrontRightDrive.isDone() == false)
 {
   this_thread::sleep_for(25);
 }
 return 0;
}


// Senses for largest object, color independent
void multipleColor()
{
  Vision6.takeSnapshot(Vision6__B_BALL);
  blueSize = Vision6.largestObject.height * Vision6.largestObject.width;
  Vision6.takeSnapshot(Vision6__R_BALL);
  redSize =  Vision6.largestObject.height * Vision6.largestObject.width;
  if(blueSize > redSize)
  {
    Vision6.takeSnapshot(Vision6__B_BALL);
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

void spinAllMotors(int motorDist)
{

  thread a = thread(spinLeft);
  // std::string b =  + ;
  // thread a = thread(spinRight);
  thread c = thread(spinFrontLeft);
  thread d = thread(spinFrontRight);
}

void coolTurn(int motorDist, int motorDir)
{
  thread a = thread(spinLeft);
  thread b = thread(spinRight);
  motorDir = motorDir * -1;
  thread c = thread(spinRight);
  thread d = thread(spinFrontRight);

}

void motorCheck()
{
while(LeftDrive.isDone() == false or FrontLeftDrive.isDone() == false or RightDrive.isDone() == false or FrontRightDrive.isDone() == false)
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
  LeftDrive.setVelocity(80, pct);
  FrontLeftDrive.setVelocity(80, pct);
  RightDrive.setVelocity(80, pct);
  FrontRightDrive.setVelocity(80, pct);
  if(SKILLZ)
  {

  }
  else
  {

  }

// New Autonomous(Home Row)
  //Move Back
  Move::moveMM(-200);

  // Turn to face goal
  Move::moveDeg(45 * INVERT_TURNS);

  // Move Forward and grab ball
  setIntakeSpeed(100);
  //setLiftSpeed(100);
  Move::moveMM(200);

  // 5. Reverse from goal, turn 180deg, reverse to goal
  setIntakeSpeed(0);
  Move::moveMM(-300);
  Move::moveDeg(175);
  Move::moveMM(-475);

  //Deposit payload
  setLiftSpeed(100);
  wait(200, msec);
  setLiftSpeed(0);

  //Move Forward, turn towards center
  Move::moveMM(500);
  Move::moveDeg(45 * INVERT_TURNS);

  //Move to center goal, turn to face away from goal
  Move::moveMM(1400);
  Move::moveDeg(-90 * INVERT_TURNS);

  //reverse to goal, deposit ball
  setLiftSpeed(100);
  setIntakeSpeed(100);
  Move::moveMM(-400);
  wait(200, msec);
  setLiftSpeed(0);
  setIntakeSpeed(0);

  //Move forward, turn towards corner goal
  Move::moveMM(200);
  Move::moveDeg(90 * INVERT_TURNS);

  //Move to corner goal, turn towards it
  Move::moveMM(1500);
  Move::moveDeg(45 * INVERT_TURNS);

  //Approach using active vision
  setIntakeSpeed(100);
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

  // Reverse, turn 180 degrees, reverse to goal
  Move::moveMM(-300);
  Move::moveDeg(175);
  Move::moveMM(-475);

  //Deposit Ball
  setLiftSpeed(100);

  //End of homerow autonomous

/*
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
    // 3. Move away from goal and turn to face other goal
    Move::moveMM(875);
    Move::moveDeg(-85 * INVERT_TURNS);

    // 4. Approach, correcting using active vision
    setIntakeSpeed(100);
    //float rightEndPosition = RightDrive.rotation(deg) + 600;
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
    //int rightOffset = rightEndPosition - RightDrive.rotation(degrees);
    //int leftOffset = leftEndPosition - LeftDrive.rotation(degrees);
    //Move::moveDeg(rightOffset - leftOffset);
    //RightDrive.spinFor(forward, -(RightDrive.rotation(degrees) - rightEndPosition), degrees);
    LeftDrive.spin(fwd, 0, pct);
    FrontLeftDrive.spin(fwd, 0, pct);
    RightDrive.spin(fwd, 0, pct);
    FrontRightDrive.spin(fwd, 0, pct);

    // 5. Reverse from goal, turn 180deg, reverse to goal
    Move::moveMM(-300);
    Move::moveDeg(170);
    Move::moveMM(-475);



    // 6. Eject payload
    setLiftSpeed(100);
  }
  */

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
  

   /*
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
         LeftDrive.spin(forward, 100, pct);
         RightDrive.spin(reverse, 100, pct);
         FrontLeftDrive.spin(forward, 100, pct);
         FrontRightDrive.spin(reverse, 100, pct);
         wait(750, msec);
         LeftDrive.setStopping(brake);
         RightDrive.setStopping(brake);
         FrontLeftDrive.setStopping(brake);
         FrontRightDrive.setStopping(brake);
         // Move::moveDeg(180, LeftDrive, FrontLeftDrive, RightDrive, FrontRightDrive);
      }
    }
    driveX = 0.75 * Controller1.Axis1.position();  // wow! 60% turn speed
    driveY = 0.85 * Controller1.Axis3.position();  // eh?  85% move speed

    //Vision6.takeSnapshot(VISION_BALL);
    
    if(Distance14.objectDistance(mm) > 350 or Distance14.objectDistance(mm) == 0)
    {
      multipleColor();
      SensorControl(5);
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

    LeftDrive.spin(forward, driveY + driveX, pct);
    RightDrive.spin(forward, driveY - driveX, pct);
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