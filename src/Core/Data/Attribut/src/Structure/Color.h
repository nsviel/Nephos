#pragma once

#include "Enum.h"

#include <glm/glm.hpp>
#include <string>


namespace dat::atr::structure{

struct Color{
  //---------------------------

  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);
  glm::vec2 range = glm::vec2(0, 5);
  std::string field = "";
  int mode = dat::atr::color::RGB;

  //---------------------------
};

}
