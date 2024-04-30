#pragma once

#include <glm/glm.hpp>

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
  void run_control(glm::vec2 center);

  //Control
  void control_keyboard_camMove();
  void control_mouse(glm::vec2 center);
  void control_mouse_wheel();

  //Subfunction
  void enable_camera_view(glm::vec2 center);
  void disable_camera_view();

private:
  vk::window::GLFW* vk_window;
  cam::Control* cam_control;
  cam::Manager* cam_manager;

  glm::vec2 cursor_pose = glm::vec2(0, 0);
};

}
