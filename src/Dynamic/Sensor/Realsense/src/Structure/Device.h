#pragma once

#include <librealsense2/rs.hpp>


namespace rlx::base{

struct Device{
  //---------------------------

  rs2::frameset frame_set;
  rs2::config configuration;
  int index = -1;

  //---------------------------
};

}
