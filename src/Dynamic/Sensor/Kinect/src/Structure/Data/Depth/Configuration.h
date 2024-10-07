#pragma once

#include <k4a/k4a.hpp>


namespace k4n::str::depth{

struct Configuration{
  //---------------------------

  std::string mode_str = "";
  std::string resolution_str = "";
  k4a_depth_mode_t mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
  uint16_t range_min = 500;
  uint16_t range_max = 4000;
  bool enabled = true;

  //---------------------------
};

}
