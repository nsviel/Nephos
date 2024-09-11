#pragma once

#include <librealsense2/rs.hpp>


namespace rlx::base{

struct Device{
  //---------------------------

  rs2::pipeline pipe;
  rs2::frameset frame_set;
  rs2::points point_set;
  rs2::config configuration;
  rs2::align aligner = rs2::align(RS2_STREAM_DEPTH);
  int index = -1;

  //---------------------------
};

}
