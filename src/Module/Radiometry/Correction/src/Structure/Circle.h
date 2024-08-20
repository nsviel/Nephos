#pragma once

#include <glm/glm.hpp>


namespace rad::cor::structure{

struct Circle{
  //---------------------------

  int radius;
  glm::ivec2 center;

  //---------------------------
};

struct Bbox{
  //---------------------------

  float scale = 2;

  //---------------------------
};

}
