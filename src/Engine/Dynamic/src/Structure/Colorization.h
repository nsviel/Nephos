#pragma once

#include <Utility/Specific/Common.h>
#include <Operation/Namespace.h>
#include <cstdint>


namespace dyn::colorization{

struct Structure{
  //---------------------------

  int color_mode = ope::color::RGB;
  int heatmap_mode = ope::color::heatmap::INTENSITY;
  glm::vec2 range_height = glm::vec2(0, 5);
  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);

  //---------------------------
};

}
