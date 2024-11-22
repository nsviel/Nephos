#pragma once

#include <glm/glm.hpp>
#include <vector>


namespace ope::tree{

struct Cube{
  int level;
  Cube* child[8];

  glm::vec3 min;
  glm::vec3 max;
  glm::vec3 center;

  std::vector<int> idx_cube;
  std::vector<int> idx_child;
};

struct Root{
  Cube* child;

  std::vector<glm::vec3>* xyz_subset;
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec4> level_rgb;
};

}
