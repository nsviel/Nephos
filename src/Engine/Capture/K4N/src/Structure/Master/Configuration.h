#pragma once

#include <k4a/k4a.hpp>
#include <string>


namespace k4n::structure{

struct FPS_{
  //---------------------------

  k4a_fps_t mode = K4A_FRAMES_PER_SECOND_30;
  std::string mode_str;
  int query;

  //---------------------------
};

struct Configuration{
  //Structure for master configuration
  //---------------------------

  k4n::structure::Depth_config depth;
  k4n::structure::Color_config color;
  k4n::structure::Infrared_config ir;
  k4n::structure::FPS_ fps;

  //---------------------------
};

}
