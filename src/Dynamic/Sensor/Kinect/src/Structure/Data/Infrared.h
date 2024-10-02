#pragma once

#include <Kinect/src/Structure/Data/Data.h>
#include <memory>

namespace utl::media{struct Image;}


namespace k4n::infrared{

struct Configuration{
  //---------------------------

  uint16_t level_min = 0;
  uint16_t level_max = 1000;
  bool enabled = true;
  int division = 1000;

  //---------------------------
};

struct Structure{
  //Structure for sensor infrared field
  //---------------------------

  k4n::infrared::Configuration config;
  k4n::structure::Data data;
  std::shared_ptr<utl::base::Image> image = std::make_shared<utl::base::Image>("Intensity");
  std::shared_ptr<utl::base::Depth> depth = std::make_shared<utl::base::Depth>("intensity_raw");

  //---------------------------
};

}
