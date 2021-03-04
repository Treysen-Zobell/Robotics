
struct Vision
{
  static unsigned int x; // center pos
  static unsigned int y;
  static unsigned int size; // area of ball, not width

  static unsigned int red;
  static unsigned int blue;
  static unsigned int any;

  static void findLargestAny();
  static void findLargestRed();
  static void findLargestBlue();
  static void findLargest(unsigned int color);
};