#pragma once

#include <Utility/Specific/Common.h>

namespace cam{class Node;}
namespace cam{class Control;}
namespace cam{class Manager;}
namespace vk::window{class GLFW;}


namespace cam::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(cam::Node* node_camera);
  ~Control();

public:
  //Main function
  void run_control(vec2 center);

  //Control
  void control_keyboard_camMove();
  void control_mouse(vec2 center);
  void control_mouse_wheel();

  //Subfunction
  void enable_camera_view(vec2 center);
  void disable_camera_view();

private:
  vk::window::GLFW* vk_window;
  cam::Control* cam_control;
  cam::Manager* cam_manager;

  vec2 cursor_pose = vec2(0, 0);
};

}
