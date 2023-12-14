#pragma once

#include <Engine/Base/Namespace.h>

#include <k4a/k4a.hpp>
#include <cstdint>


namespace eng::kinect::structure{

struct Cloud{
  //---------------------------

  eng::structure::Object* object;

  /*
  * 0 -> camera color
  * 1 -> unicolor
  * 2 -> heatmap
  */
  int color_mode = 0;

  //---------------------------
};

}
