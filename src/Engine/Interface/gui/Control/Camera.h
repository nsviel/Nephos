#pragma once

#include <glm/glm.hpp>

namespace itf{class Node;}
namespace itf{class Structure;}
namespace cam{class Control;}
namespace cam{class Manager;}
namespace cam{class Structure;}
namespace vk::window{class GLFW;}
namespace itf::control{class Camera;}


namespace itf::gui{

class Camera
{
public:
  //Constructor / Destructor
  Camera(itf::Node* node_interface);
  ~Camera();

public:
  //Main function
  void run_control(glm::vec2 center);

  //Subfunction
  void control_keyboard_camMove();
  void control_mouse(glm::vec2 center);
  void control_mouse_wheel();

private:
  vk::window::GLFW* vk_window;
  cam::Control* cam_control;
  cam::Manager* cam_manager;
  cam::Structure* cam_struct;
  itf::Structure* itf_struct;
  itf::control::Camera* itf_camera;
};

}
