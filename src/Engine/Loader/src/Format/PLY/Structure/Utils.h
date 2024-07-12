#pragma once

#include <Utility/Namespace.h>
#include <string>


namespace format::ply{

struct Data{
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec3> rgb;
  std::vector<float> Is;
  std::vector<float> ts;
};

}
