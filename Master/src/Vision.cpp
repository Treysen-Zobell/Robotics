
#include "Vision.h"
#include <vex.h>

unsigned int Vision::x = 0;
unsigned int Vision::y = 0;
unsigned int Vision::size = 0;

unsigned int Vision::red = 0;
unsigned int Vision::blue = 1;
unsigned int Vision::any = 2;

void Vision::findLargestAny()
{
  Vision6.takeSnapshot(Vision6__B_BALL);
  unsigned int blueSize = Vision6.largestObject.height * Vision6.largestObject.width;
  unsigned int blueX = Vision6.largestObject.centerX;
  unsigned int blueY = Vision6.largestObject.centerY;

  Vision6.takeSnapshot(Vision6__R_BALL);
  unsigned int redSize =  Vision6.largestObject.height * Vision6.largestObject.width;
  unsigned int redX = Vision6.largestObject.centerX;
  unsigned int redY = Vision6.largestObject.centerY;
  
  if (blueSize > redSize)
  {
    Vision::size = blueSize;
    Vision::x = blueX;
    Vision::y = blueY;
  }
  else
  {
    Vision::size = redSize;
    Vision::x = redX;
    Vision::y = redY;
  }
}

void Vision::findLargestRed()
{
  Vision6.takeSnapshot(Vision6__R_BALL);
  Vision::size = Vision6.largestObject.height * Vision6.largestObject.width;
  Vision::x = Vision6.largestObject.centerX;
  Vision::y = Vision6.largestObject.centerY;
}

void Vision::findLargestBlue()
{
  Vision6.takeSnapshot(Vision6__B_BALL);
  Vision::size = Vision6.largestObject.height * Vision6.largestObject.width;
  Vision::x = Vision6.largestObject.centerX;
  Vision::y = Vision6.largestObject.centerY;
}

void Vision::findLargest(unsigned int color)
{
  if (color == Vision::red) { Vision::findLargestRed(); }
  else if (color == Vision::blue) { Vision::findLargestBlue(); }
  else if (color == Vision::any) { Vision::findLargestAny(); }
}