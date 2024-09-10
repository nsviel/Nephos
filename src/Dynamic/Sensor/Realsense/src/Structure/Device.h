#pragma once

#include <librealsense2/rs.hpp>


namespace rlx::base{

struct Device{
  //---------------------------

  rs2::frameset frameset;
  int index = -1;

  //---------------------------
};

}
