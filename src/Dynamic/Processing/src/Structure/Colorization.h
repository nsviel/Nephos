#pragma once

#include <Data/Attribut/Namespace.h>
#include <glm/glm.hpp>


namespace dyn::prc::colorization{

struct Structure{
  //---------------------------

  int color_mode = dat::atr::color::RGB;
  glm::vec2 range = glm::vec2(0, 5);
  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);

  //---------------------------
};

}
