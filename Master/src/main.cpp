#include "vex.h"

#include "Vision.h"
#include "Robot.h"
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

int driveX;
int driveY;
int ldrive; 
int rdrive;
int motorDir;
int motorDist;
int startPosition;
int blueSize;
int redSize;

// Beginning of match functions
void pre_auton(void)
{
  vexcodeInit();
}

//Autonomous Function(s):
void autonomous(void)
{
  Robot::setDriveSpeed(60);

  if(MODE == 2) //skills  //////////////////////////////////////////////////////////////////////////////////////
  {

  //Turns and deposits preload into goal, turns to face ball
  Move::moveDeg(20);
  Robot::setLiftSpeed(100);
  wait(400, msec);
  Robot::setLiftSpeed(0);
  Move::moveDeg(10);

  //Moves Forward and grabs first ball
  Robot::setIntakeSpeed(100);
  Robot::driveForward(500, 50, true, true, 3.5, Vision::any);
  Robot::driveForward(600, 50, true, true, 4, Vision::any);
  Robot::setIntakeSpeed(0);
  Robot::brake();

  //Turns to face away from corner goal, backs up to goal
  Robot::setDriveSpeed(50); Move::moveDeg(100);
  Robot::brake();
  Robot::setIntakeSpeed(100);
  Robot::setLiftSpeed(100);
  Robot::driveForward(-350, 80, true, true, 43, Vision::any);

  //Deposits ball
  wait(1700, msec);
  Robot::setLiftSpeed(0);

  //Moves forward and grabs ball on the center line
  Move::moveMM(200);
  Robot::brake();
  Move::moveDeg(-35);
  Robot::brake();
  Robot::driveForward(1350, 80, true, true, 4, Vision::any);
  Robot::brake();

  //Turns away from side goal, deposits ball 
  Move::moveDeg(90);
  Robot::brake();
  Robot::setLiftSpeed(100);
  Robot::driveForward(-150, 80, true, true, 4, Vision::any);
  Robot::brake();
  wait(1500, msec);
  Robot::setLiftSpeed(0);

  //uses vision to line up, grabs other ball
  Robot::driveForward(450, 50, true, true, 3.5, Vision::any);
  Robot::brake();

  // Turns and grabs ball near corner goal
  Move::moveMM(200);
  Robot::brake();
  Move::moveDeg(-90);
  Robot::brake();
  Robot::driveForward(1400, 70, true, true, 4, Vision::any);
  Robot::brake();

  // Backs up, turns away from corner goal, backs up using vision
  Move::moveMM(-650);
  Robot::brake();
  Move::moveDeg(145);
  Robot::brake();
  Robot::setLiftSpeed(50);
  Robot::driveForward(-700, 70, true, true, 4, Vision::any);
  Robot::brake();
  Robot::setIntakeSpeed(0);
  Robot::setLiftSpeed(100);
  wait(1500, msec);
  Robot::setLiftSpeed(0);

  //Moves away from goal, turns toward ball and grabs it
  Move::moveMM(250);
  Robot::brake();
  Robot::brake();
  Robot::setIntakeSpeed(100);
  Robot::driveForward(1575, 80, true, true, 4, Vision::any);

  //Turns away from side goal, backs up to it using vision
  Move::moveDeg(85);
  Robot::brake();
  Robot::driveForward(-700, 70, true, true, 4, Vision::any);
  Robot::setLiftSpeed(100);
  wait(1000, msec);
}

if(MODE == 0) // Homerow auton //////////////////////////////////////////////////////
{

  //SimpleMove Back
  Move::moveMM(-250);
  Robot::brake();

  // Turn to face goal
  Move::moveDeg(45 * INVERT_TURNS);

  // Move Forward and grab ball
  Robot::setIntakeSpeed(100);
  Robot::driveForward(200, 80, true, true, 3, Vision::any);
  Robot::brake();

  // 5. Reverse from goal, turn sideways, move forward 
  Robot::setIntakeSpeed(0);
  Robot::setDriveSpeed(80); Move::moveMM(-225);
  Robot::brake();
  Move::moveDeg(60);
  Robot::brake();
  Move::moveMM(150);

  // Turn to face away from goal, back up using vision
  Move::moveDeg(100);
  Robot::driveForward(-300, 75, true, true, 3.5, Vision::any);
  Robot::brake();
  wait(400, msec);

  //Deposit payload
  Robot::setLiftSpeed(100);
  wait(500, msec);
  Robot::setLiftSpeed(0);

  //Move Forward, turn towards center
  Move::moveMM(500);
  Move::moveDeg(45 * INVERT_TURNS);

  //Move to center goal, turn to face away from goal
  Robot::setDriveSpeed(90); Move::moveMM(1200);
  Move::moveDeg(-85 * INVERT_TURNS);
  Robot::brake();

  //reverse to goal, deposit ball
  Robot::setLiftSpeed(80);
  Robot::setIntakeSpeed(80);
  Robot::driveForward(-150, 70, true, true, 3.5, Vision::any);
  Robot::brake();
  Robot::setLiftSpeed(100);
  Robot::setIntakeSpeed(100);
  wait(1300, msec);
  Robot::setLiftSpeed(0);
  Robot::setIntakeSpeed(0);

  //SimpleMove forward, turn towards corner goal
  Move::moveMM(400);
  Move::moveDeg(90 * INVERT_TURNS);
  Robot::brake();

  //SimpleMove to corner goal, turn towards it
  Move::moveMM(950);
  Robot::brake();
  Move::moveDeg(50 * INVERT_TURNS);
  Robot::brake();

  //Approach using active vision
  Robot::setIntakeSpeed(100);
  Robot::driveForward(400, 80, true, true, 3, Vision::any);

  // Reverse, turn 180 degrees, reverse to goal
  Move::moveMM(-160);
  Robot::brake();
  Move::moveDeg(170);
  Robot::brake();
  Move::moveMM(-265);
  Robot::brake();

  //Deposit Ball
  Robot::setLiftSpeed(100);
  //End of homerow autonomous
  }

  if(MODE == 1) // One/two tower auton  ///////////////////////////////////////////////////
  {
    // 1. Turn
    Move::moveDeg(20 * INVERT_TURNS);

    // 2. Deposit preload
    Robot::setIntakeSpeed(100);
    Robot::setLiftSpeed(100);

    wait(1000, msec);

    Move::moveDeg(25 * INVERT_TURNS);

    Robot::setIntakeSpeed(0);
    Robot::setLiftSpeed(0);

    if (!CORNER_ONLY)
    {
      // 3. SimpleMove away from goal and turn to face other goal
      Move::moveMM(900);
      Move::moveDeg(-80 * INVERT_TURNS);

      // 4. Approach, correcting using active vision
      Robot::setIntakeSpeed(100);
      Robot::driveForward(600, 80, true, true, 3, Vision::any);
      Robot::brake();

      // 5. Reverse from goal, turn 180deg, reverse to goal
      Robot::setIntakeSpeed(0);
      Robot::setDriveSpeed(80);
      Move::moveMM(-250);
      Robot::brake();
      Move::moveDeg(190);
      Robot::brake();
      Move::moveMM(-275);

      // 6. Eject payload
      Robot::setLiftSpeed(100);
      Robot::setIntakeSpeed(100);
    }
  }
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
      }
    }
    driveX = TURN_SPEED * Controller1.Axis1.position();
    driveX += SLOW_TURN_SPEED * Controller1.Axis4.position();
    driveY = DRIVE_SPEED * Controller1.Axis3.position();
    
    if((Distance14.objectDistance(mm) > 350 or Distance14.objectDistance(mm) == 0) && driveY >= 0)
    {
      Robot::driveForward(0, 0, false, true, 4.5, Vision::any);
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
    Robot::chainControl();
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