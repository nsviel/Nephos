#pragma once

#include <librealsense2/rs.hpp>


namespace rlx{

struct Structure{
  //---------------------------

  rs2::context context;
  rs2::pipeline pipe;
  int nb_device = 0;
  int current_ID = 0;

  //---------------------------
};

}
