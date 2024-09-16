#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace vk{class Interface;}
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
  glm::mat4 compute_proj_perspective(std::shared_ptr<cam::Entity> camera);

private:
  vk::Interface* vk_interface;
};

}
