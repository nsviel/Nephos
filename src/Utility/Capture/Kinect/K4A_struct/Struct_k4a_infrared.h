#pragma once

#include <k4a/k4a.hpp>
#include <string>


namespace util::kinect::structure{

struct Struct_k4a_infrared{
  //---------------------------

  uint16_t level_min = 0;
  uint16_t level_max = 1000;

  //---------------------------
};

}
