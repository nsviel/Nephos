#pragma once

#include <glm/glm.hpp>
#include <string>
#include <memory>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}


namespace k4n{

class Utils
{
public:
  //Constructor / Destructor
  Utils(k4n::Node* node_k4n);
  ~Utils();

public:
  //Main function
  glm::vec3 convert_depth_2d_to_3d(std::shared_ptr<k4n::base::Sensor> sensor, glm::ivec2 point_2d);

private:

};

}
