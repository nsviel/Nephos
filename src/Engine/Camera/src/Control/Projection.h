#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Element/Namespace.h>

namespace vk::window{class GLFW;}
namespace eng::cam{class Node;}


namespace eng::cam{

class Projection
{
public:
  Projection(eng::cam::Node* node_camera);
  ~Projection();

public:
  //Main function
  mat4 compute_proj_perspective(utl::entity::Camera* camera);
  mat4 compute_proj_ortho(utl::entity::Camera* camera);

  //Subfunction
  void ortho_zoom(utl::entity::Camera* camera, float value);

private:
  vk::window::GLFW* vk_window;
};

}
