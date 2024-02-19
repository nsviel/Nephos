#pragma once

#include <Utility/Specific/common.h>

#include <k4a/k4a.hpp>
#include <cstdint>


namespace k4n::transformation{

enum Mode{
  DEPTH_TO_COLOR = 0,
  COLOR_TO_DEPTH = 1,
};

}

namespace k4n::structure{

struct Operation{
  //---------------------------

  /*
  * 0 -> camera color
  * 1 -> colored unicolor
  * 2 -> white unicolor
  * 3 -> heatmap
  */
  int color_mode = 0;
  int heatmap_mode = 0;
  int intensity_division = 1000;
  int transformation_mode = k4n::transformation::COLOR_TO_DEPTH;
  glm::vec2 range_height = glm::vec2(-1, 1);
  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);

  //---------------------------
};

}
