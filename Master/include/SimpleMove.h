
#include <vex.h>

class VexThread
{
  float currentPos = 0.0f;
  float destinationPos = 0.0f;
  bool moveComplete = true;
  vex::thread thread;

  VexThread();
  ~VexThread();
};

class SimpleMove
{
  static void moveMM(int amount);
  static void moveDeg(int amount);

  static VexThread l1;
  static VexThread l2;
  static VexThread r1;
  static VexThread r2;
};