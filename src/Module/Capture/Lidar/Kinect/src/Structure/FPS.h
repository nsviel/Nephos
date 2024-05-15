#pragma once

#include <Kinect/src/Structure/Color.h>
#include <Kinect/src/Structure/Depth.h>
#include <Kinect/src/Structure/Infrared.h>
#include <k4a/k4a.hpp>
#include <string>


namespace k4n::structure{

struct FPS{
  //---------------------------

  k4a_fps_t mode = K4A_FRAMES_PER_SECOND_30;
  std::string mode_str;
  int query;

  //---------------------------
};

}
