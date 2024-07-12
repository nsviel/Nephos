#pragma once

#include <glm/glm.hpp>


namespace ope::color{

struct Configuration{
  //---------------------------

  glm::vec4 unicolor;
  glm::vec2 heatmap_range_height;
  float intensity_diviser;
  int color_mode;
  int heatmap_mode;

  //---------------------------
};

}
