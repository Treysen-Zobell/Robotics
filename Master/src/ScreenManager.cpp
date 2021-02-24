
#include "vex.h"

#include "ScreenManager.h"

ScreenManager::ScreenManager()
{
  this->poll();
}

ScreenManager::~ScreenManager()
{

}

void ScreenManager::updateThread()
{
  while (!this->shouldExit)
  {
    if (Brain.Screen.xPosition() != this->lastX || Brain.Screen.yPosition() != this->lastY)
    {
      this->pressed = true;
      this->poll();
    }
    vex::wait(50, vex::msec);
  }
}

void ScreenManager::poll()
{
  this->lastX = Brain.Screen.xPosition();
  this->lastY = Brain.Screen.yPosition();
}
