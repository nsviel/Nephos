#pragma once

#include <Kinect/src/Structure/Data.h>
#include <k4a/k4a.hpp>

namespace utl::media{struct Image;}


namespace k4n::depth{

enum Mode{
  DEPTH_TO_COLOR = 0,
  COLOR_TO_DEPTH = 1,
};

struct Configuration{
  //---------------------------

  k4a_depth_mode_t mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
  std::string mode_str = "";
  std::string firmware_version = "";
  std::string resolution = "";
  uint16_t range_min = 500;
  uint16_t range_max = 4000;
  bool enabled = true;
  int transformation_mode = k4n::depth::COLOR_TO_DEPTH;

  //---------------------------
};

struct Structure{
  //Structure for sensor depth field
  //---------------------------

  k4n::depth::Configuration config;
  k4n::structure::Data data;
  k4n::structure::Data cloud;
  utl::media::Image image;

  //---------------------------
};

}
