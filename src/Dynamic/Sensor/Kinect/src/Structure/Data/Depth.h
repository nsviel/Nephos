#pragma once

#include <Kinect/src/Structure/Data/Data.h>
#include <k4a/k4a.hpp>
#include <memory>

namespace utl::media{struct Image;}


namespace k4n::depth{

struct Configuration{
  //---------------------------

  k4a_depth_mode_t mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
  uint16_t range_min = 500;
  uint16_t range_max = 4000;
  bool enabled = true;

  //---------------------------
};

struct Structure{
  //Structure for sensor depth field
  //---------------------------

  k4n::depth::Configuration config;
  k4n::structure::Data data;
  std::shared_ptr<utl::media::Image> image_raw = std::make_shared<utl::media::Image>("depth_raw");
  std::shared_ptr<utl::media::Image> image_colored = std::make_shared<utl::media::Image>("Depth");
  std::shared_ptr<utl::media::Image> table_xy = std::make_shared<utl::media::Image>("depth_table_xy");

  //---------------------------
};

}
