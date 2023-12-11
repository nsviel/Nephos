#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>


namespace util::base{

struct Video{
  //---------------------------

  int64_t start_time;
  int64_t duration;
  int64_t bit_rate;
  int fps;
  int width;
  int height;

  //---------------------------
};

}
