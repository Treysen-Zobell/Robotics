#include <vex.h>

class DriveBase
{
public:
  static vex::motor rearLeftMotor;
  static vex::motor frontLeftMotor;
  static vex::motor rearRightMotor;
  static vex::motor frontRightMotor;
  
  static void init(vex::motor l1, vex::motor l2, vex::motor r1, vex::motor r2);

private:
};
