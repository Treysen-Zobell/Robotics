
#include <vex.h>

#include <vector>

struct Move
{
  static float leftPos;
  static float rightPos;

  static void leftRear();
  static void leftFront();
  static void rightRear();
  static void rightFront();

  static void moveMM(int distance);
  static void moveDeg(int deg);
};