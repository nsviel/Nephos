#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "../Utility_namespace.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace glm;

class Config;


namespace utility{
class UTL_window
{
public:
  //Constructor / Destructor
  UTL_window(Config* config);
  ~UTL_window();

public:
  //Main functions
  void create_window();
  void close_window();
  void destroy_window();

  //Subfunction
  void set_window_size_minimum(int width, int height);
  void set_window_size_maximum(int width, int height);

  //Operation function
  void manage_input();
  vec2 compute_window_dim();
  bool check_for_resizing();
  bool window_should_close();

  //Mouse
  glm::vec2 get_mouse_pose();
  void set_mouse_pose(glm::vec2 pos);

  inline GLFWwindow* get_window(){return window;}
  inline vec2 get_window_dim(){return window_dim;}
  inline vec2 get_window_center(){return window_center;}
  inline void set_window_center(vec2 value){this->window_center = value;}

private:
  Config* config;
  GLFWwindow* window;

  vec2 window_dim;
  vec2 window_dim_min;
  vec2 window_dim_max;
  vec2 window_center;
  bool has_been_resized;
};
}

#endif
