#pragma once

#include <glm/glm.hpp>

namespace cam{class Node;}
namespace cam{class Control;}
namespace cam{class Manager;}
namespace cam{class Structure;}
namespace vk::window{class GLFW;}


namespace itf::control{

class Camera
{
public:
  //Constructor / Destructor
  Camera(cam::Node* node_camera);
  ~Camera();

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
  cam::Structure* cam_struct;

  glm::vec2 cursor_pose = glm::vec2(0, 0);
};

}
