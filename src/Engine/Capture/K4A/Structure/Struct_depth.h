#pragma once

#include <k4a/k4a.hpp>
#include <string>


namespace eng::kinect::structure{

struct Depth_config{
  //---------------------------

  bool enabled = true;
  k4a_depth_mode_t mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
  uint16_t range_min = 500;
  uint16_t range_max = 4000;

  //---------------------------
};

struct Depth{
  //---------------------------

  eng::kinect::structure::Depth_config config;
  eng::kinect::structure::Image image;

  //---------------------------
};

}
