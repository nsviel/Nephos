#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Element/Namespace.h>

namespace vk::window{class GLFW;}
namespace cam{class Node;}
namespace cam{class Camera;}


namespace cam{

class Projection
{
public:
  Projection(cam::Node* node_camera);
  ~Projection();

public:
  //Main function
  mat4 compute_proj_perspective(cam::Camera* camera);
  mat4 compute_proj_ortho(cam::Camera* camera);

  //Subfunction
  void ortho_zoom(cam::Camera* camera, float value);

private:
  vk::window::GLFW* vk_window;
};

}
