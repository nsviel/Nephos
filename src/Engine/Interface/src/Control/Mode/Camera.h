#pragma once

#include <glm/glm.hpp>

namespace itf{class Node;}
namespace itf{class Structure;}
namespace cam{class Control;}
namespace cam{class Manager;}
namespace cam{class Structure;}
namespace vk::window{class GLFW;}


namespace itf::control{

class Camera
{
public:
  //Constructor / Destructor
  Camera(itf::Node* node_interface);
  ~Camera();

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
  void enable_camera_view(glm::vec2 center);
  void disable_camera_view();

private:
  itf::Structure* itf_struct;
  vk::window::GLFW* vk_window;
  cam::Control* cam_control;
  cam::Manager* cam_manager;
  cam::Structure* cam_struct;
};

}
