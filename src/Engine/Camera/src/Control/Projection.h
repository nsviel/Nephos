#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Element/Namespace.h>

namespace vk::window{class GLFW;}
namespace cam{class Node;}
namespace cam{class Entity;}


namespace cam{

class Projection
{
public:
  Projection(cam::Node* node_camera);
  ~Projection();

public:
  //Main function
  mat4 compute_proj_perspective(cam::Entity* camera);
  mat4 compute_proj_ortho(cam::Entity* camera);

  //Subfunction
  void ortho_zoom(cam::Entity* camera, float value);

private:
  vk::window::GLFW* vk_window;
};

}
