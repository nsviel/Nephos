#pragma once

#include <Utility/Specific/Common.h>

namespace eng::cam{class Node;}
namespace eng::cam{class Control;}
namespace eng::cam{class Manager;}
namespace vk::window{class GLFW;}


namespace eng::cam::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(eng::cam::Node* node_camera);
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
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;

  vec2 cursor_pose = vec2(0, 0);
};

}
