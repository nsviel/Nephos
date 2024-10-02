#pragma once

#include <Kinect/src/Structure/Data/Data.h>
#include <k4a/k4a.hpp>
#include <memory>

namespace utl::media{class Image;}
namespace utl::media{class Storage;}


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
  std::shared_ptr<utl::base::Image> image = std::make_shared<utl::base::Image>("Depth");
  std::shared_ptr<utl::base::Depth> depth = std::make_shared<utl::base::Depth>("depth_raw");
  std::shared_ptr<utl::base::Storage> table_xy = std::make_shared<utl::base::Storage>("depth_table_xy");

  //---------------------------
};

}
