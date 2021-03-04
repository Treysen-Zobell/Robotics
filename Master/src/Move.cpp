
#include "Move.h"

#include <algorithm>
#include <cmath>

float Move::leftPos = 0;
float Move::rightPos = 0;

void Move::leftRear()
{
  RearLeftDrive.spinFor(vex::directionType::fwd, Move::leftPos, vex::deg);
  while (!RearLeftDrive.isDone()) { wait(10, vex::msec); }
}

void Move::leftFront()
{
  FrontLeftDrive.spinFor(vex::directionType::fwd, Move::leftPos, vex::deg);
  while (!FrontLeftDrive.isDone()) { wait(10, vex::msec); }
}

void Move::rightRear()
{
  RearRightDrive.spinFor(vex::directionType::fwd, Move::rightPos, vex::deg);
  while (!RearRightDrive.isDone()) { wait(10, vex::msec); }
}

void Move::rightFront()
{
  FrontRightDrive.spinFor(vex::directionType::fwd, Move::rightPos, vex::deg);
  while (!FrontRightDrive.isDone()) { wait(10, vex::msec); }
}

void Move::moveMM(int mm)
{
  Move::leftPos = (int)(mm * 1.13);
  Move::rightPos = (int)(mm * 1.13);
  vex::thread l1(Move::leftRear);
  vex::thread l2(Move::leftFront);
  vex::thread r1(Move::rightRear);
  vex::thread r2(Move::rightFront);
  l1.join();
  l2.join();
  r1.join();
  r2.join();
}

void Move::moveDeg(int deg)
{
  Move::leftPos = (int)(deg * 3.6);
  Move::rightPos = -(int)(deg * 3.6);
  vex::thread l1(Move::leftRear);
  vex::thread l2(Move::leftFront);
  vex::thread r1(Move::rightRear);
  vex::thread r2(Move::rightFront);
  l1.join();
  l2.join();
  r1.join();
  r2.join();
}
