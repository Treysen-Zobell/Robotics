
#include <vector>

struct Button
{
  int xPos;
  int yPos;
  int width;
  int height;

  Button();
  Button(int x, int y, int width, int height);
  ~Button();

  void draw();
  void pressed();
};

struct ScreenManager
{
  int lastX;
  int lastY;
  bool pressed;
  bool shouldExit = false;
  std::vector<Button> buttons();

  ScreenManager();
  ~ScreenManager();

  void updateThread();
  void poll();
};
