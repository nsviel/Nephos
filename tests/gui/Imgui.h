#pragma once

#include <GLFW/glfw3.h>


namespace test{

class Imgui
{
public:
  Imgui();
  ~Imgui();

public:
  //Main function
  void run();
  void design();

  //Subfunction
  void init();
  void loop();
  void clean();

private:
  GLFWwindow* window = nullptr;
};

}
