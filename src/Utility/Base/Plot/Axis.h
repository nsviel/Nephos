#pragma once

#include <glm/glm.hpp>
#include <vector>


namespace utl::base{

struct Axis{
  //---------------------------

  //Data
  int size = 0;
  float min = 0;
  float max = 0;
  float current = 0;
  float resolution = 0;
  std::vector<float> data;
  std::vector<float> fitting;
  glm::vec2 bound = glm::vec2(0, 0);

  //---------------------------
};

}
