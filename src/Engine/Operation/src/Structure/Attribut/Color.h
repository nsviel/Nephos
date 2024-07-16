#pragma once

#include <Operation/Namespace.h>
#include <glm/glm.hpp>


namespace ope::attribut{

struct Color{
  //---------------------------

  glm::vec2 range_height = glm::vec2(0, 5);
  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);
  int heatmap_mode = ope::heatmap::INTENSITY;
  int color_mode = ope::color::RGB;

  //---------------------------
};

}
