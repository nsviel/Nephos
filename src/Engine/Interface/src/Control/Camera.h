#pragma once

#include <glm/glm.hpp>

namespace itf{class Node;}
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


private:
  vk::window::GLFW* vk_window;
  cam::Control* cam_control;
  cam::Manager* cam_manager;
  cam::Structure* cam_struct;

  glm::vec2 cursor_pose = glm::vec2(0, 0);
};

}
