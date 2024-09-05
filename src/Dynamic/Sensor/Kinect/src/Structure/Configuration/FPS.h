#pragma once

#include <k4a/k4a.hpp>


namespace k4n::structure{

struct FPS{
  //---------------------------

  k4a_fps_t mode = K4A_FRAMES_PER_SECOND_30;
  int query;

  //---------------------------
};

}
