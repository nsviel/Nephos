#pragma once

#include <Utility/Specific/common.h>

class Configuration;


namespace utl::element{

class Window
{
public:
  //Constructor / Destructor
  Window(Configuration* config);
  ~Window();

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
  Configuration* config = nullptr;
  GLFWwindow* window = nullptr;

  vec2 window_dim;
  vec2 window_dim_min;
  vec2 window_dim_max;
  vec2 window_center;
  bool has_been_resized;
};

}
