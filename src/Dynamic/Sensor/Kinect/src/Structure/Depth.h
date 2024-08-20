#pragma once

#include <Kinect/src/Structure/Data.h>
#include <k4a/k4a.hpp>

namespace utl::media{struct Image;}


namespace k4n::depth{

struct Configuration{
  //---------------------------

  k4a_depth_mode_t mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
  std::string mode_str = "";
  std::string firmware_version = "";
  std::string resolution = "";
  uint16_t range_min = 500;
  uint16_t range_max = 4000;
  bool enabled = true;

  //---------------------------
};

struct Structure{
  //Structure for sensor depth field
  //---------------------------

  k4n::depth::Configuration config;
  k4n::structure::Data data;
  utl::media::Image image;

  //---------------------------
};

}
