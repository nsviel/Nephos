#pragma once

#include <Kinect/src/Structure/Data.h>
#include <k4a/k4a.hpp>


namespace k4n::transformation{

enum Mode{
  DEPTH_TO_COLOR = 0,
  COLOR_TO_DEPTH = 1,
};

struct Structure{
  //---------------------------

  int mode = k4n::transformation::COLOR_TO_DEPTH;

  //Color to depth coordinate mapping
  glm::ivec4 table_xy;

  //---------------------------
};

}
