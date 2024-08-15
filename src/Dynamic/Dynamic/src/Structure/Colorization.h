#pragma once

#include <Data/Namespace.h>
#include <glm/glm.hpp>


namespace dyn::colorization{

struct Structure{
  //---------------------------

  int color_mode = dat::atr::color::RGB;
  int heatmap_mode = dat::atr::heatmap::INTENSITY;
  glm::vec2 range = glm::vec2(0, 5);
  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);

  //---------------------------
};

}
