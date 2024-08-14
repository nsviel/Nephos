#pragma once

#include <glm/glm.hpp>

namespace ctr{class Node;}
namespace ctr{class Structure;}
namespace cam{class Control;}
namespace cam{class Manager;}
namespace cam{class Structure;}
namespace vk::window{class GLFW;}


namespace ctr::mode{

class Navigation
{
public:
  //Constructor / Destructor
  Navigation(ctr::Node* node_control);
  ~Navigation();

public:
  //Main function
  void cam_forward();
  void cam_backward();
  void cam_left();
  void cam_right();
  void cam_down();
  void cam_up();
  void cam_zoom(float value);

  //Subfunction
  void enable_camera_view();
  void disable_camera_view();

private:
  ctr::Structure* ctr_struct;
  vk::window::GLFW* vk_window;
  cam::Control* cam_control;
  cam::Manager* cam_manager;
  cam::Structure* cam_struct;
};

}
