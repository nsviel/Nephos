#pragma once

#include <Kinect/src/Structure/FPS.h>
#include <Kinect/src/Structure/Color.h>
#include <Kinect/src/Structure/Depth.h>
#include <Kinect/src/Structure/Infrared.h>
#include <k4a/k4a.hpp>
#include <string>


namespace k4n::structure{

struct Configuration{
  //Structure for master configuration
  //---------------------------

  k4n::structure::Depth_config depth;
  k4n::structure::Color_config color;
  k4n::structure::Infrared_config ir;
  k4n::structure::Synchro synchro;
  k4n::structure::FPS fps;

  //---------------------------
};

}
