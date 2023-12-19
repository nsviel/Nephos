#pragma once

#include <Engine/Base/Namespace.h>

#include <k4a/k4a.hpp>
#include <cstdint>


namespace eng::kinect::structure{

struct Cloud{
  //---------------------------

  eng::structure::Cloud* object;
  std::vector<glm::vec3> vec_corner;

  /*
  * 0 -> camera color
  * 1 -> colored unicolor
  * 2 -> white unicolor
  * 3 -> heatmap
  */
  int color_mode = 2;

  //---------------------------
};

}
