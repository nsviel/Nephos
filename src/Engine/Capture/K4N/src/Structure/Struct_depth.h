#pragma once

#include <k4a/k4a.hpp>
#include <string>


namespace eng::k4n::structure{

struct Depth_config{
  //---------------------------

  bool enabled = true;

  k4a_depth_mode_t mode = K4A_DEPTH_MODE_NFOV_UNBINNED;

  std::string mode_str;
  std::string firmware_version;

  uint16_t range_min = 500;
  uint16_t range_max = 4000;

  //---------------------------
};

struct Depth{
  //---------------------------

  eng::k4n::structure::Depth_config config;
  eng::k4n::structure::Image image;
  eng::k4n::structure::Image image_to_color;

  //---------------------------
};

}
