
#include "vex.h"

#include <vector>

class MoveThread
{
private:
  bool complete = false;

public:
  int holdDuration = 0;
  int movePhase = 0;

  float startPos;
  float endPos;

  vex::directionType dir;
  vex::motor encoderMotor;
  vex::motor motor;

  MoveThread(vex::motor motor, vex::motor encoderMotor, float distance);
  ~MoveThread();

  void start();
  void update();
  bool done();
  float getPos();
};
