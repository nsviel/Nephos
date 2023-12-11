#pragma once

#include <k4a/k4a.hpp>
#include <string>


namespace util::kinect::structure{

struct Struct_k4a_depth{
  //---------------------------

  bool enabled = true;
  k4a_depth_mode_t mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
  uint16_t range_min = 500;
  uint16_t range_max = 4000;

  //---------------------------
};

}
