#pragma once

#include <glm/glm.hpp>

namespace vk::window{class GLFW;}
namespace cam{class Node;}
namespace cam{class Entity;}


namespace cam::projection{

class Perspective
{
public:
  Perspective(cam::Node* node_camera);
  ~Perspective();

public:
  //Main function
  glm::mat4 compute_proj_perspective(cam::Entity* camera);

private:
  vk::window::GLFW* vk_window;
};

}
