#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace cam{class Node;}
namespace cam{class Entity;}


namespace cam::projection{

class Orthographic
{
public:
  Orthographic(cam::Node* node_camera);
  ~Orthographic();

public:
  //Main function
  glm::mat4 compute_projection(std::shared_ptr<cam::Entity> camera);

  //Subfunction
  void camera_zoom(std::shared_ptr<cam::Entity> camera, float value);

private:

};

}
