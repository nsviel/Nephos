#pragma once

#include <glm/glm.hpp>

namespace itf{class Node;}
namespace itf{class Structure;}
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
  void control_keyboard();
  void control_mouse(glm::vec2 center);
  void control_wheel();

private:
  itf::Structure* itf_struct;
  itf::control::Camera* itf_camera;
};

}
