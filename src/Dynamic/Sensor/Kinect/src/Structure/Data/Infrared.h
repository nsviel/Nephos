#pragma once

#include <Kinect/src/Structure/Data/Data.h>
#include <memory>

namespace utl::media{struct Image;}


namespace k4n::infrared{

struct Configuration{
  //---------------------------

  bool enabled = true;
  int division = 1000;

  uint16_t level_min = 0;
  uint16_t level_max = 1000;

  //---------------------------
};

struct Structure{
  //Structure for sensor infrared field
  //---------------------------

  k4n::infrared::Configuration config;
  k4n::structure::Data data;
  std::shared_ptr<utl::media::Image> image;

  //---------------------------
};

}
