#pragma once

#include <glm/glm.hpp>

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
  glm::mat4 compute_proj_perspective(cam::Entity* camera);
  glm::mat4 compute_proj_ortho(cam::Entity* camera);

  //Subfunction
  void ortho_zoom(cam::Entity* camera, float value);

private:
  vk::window::GLFW* vk_window;
};

}
