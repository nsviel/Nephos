#pragma once

#include <Kinect/src/Structure/Data.h>
#include <k4a/k4a.hpp>


namespace k4n::structure{

struct Depth_config{
  //---------------------------

  bool enabled = true;

  k4a_depth_mode_t mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;

  uint16_t range_min = 500;
  uint16_t range_max = 4000;

  //---------------------------
};

struct Depth{
  //Structure for sensor depth field
  //---------------------------

  k4n::structure::Depth_config config;
  k4n::structure::Data data;
  k4n::structure::Data cloud;

  //---------------------------
};

}
