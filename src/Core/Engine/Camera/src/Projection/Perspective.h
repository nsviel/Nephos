#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace cam{class Node;}
namespace cam{class Entity;}
namespace vk::interface{class Window;}


namespace cam::projection{

class Perspective
{
public:
  Perspective(cam::Node* node_camera);
  ~Perspective();

public:
  //Main function
  glm::mat4 compute_projection(std::shared_ptr<cam::Entity> camera);

private:
  vk::interface::Window* vk_window;
};

}
