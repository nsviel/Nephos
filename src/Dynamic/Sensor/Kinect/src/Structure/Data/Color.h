#pragma once

#include <Kinect/src/Structure/Data/Data.h>
#include <Utility/Namespace.h>
#include <k4a/k4a.hpp>
#include <memory>

namespace k4n::structure{struct Data;}
namespace utl::media{struct Image;}


namespace k4n::color{

struct Configuration{
  //---------------------------

  //General
  bool enabled = true;

  k4a_image_format_t format = K4A_IMAGE_FORMAT_COLOR_YUY2;
  k4a_color_resolution_t resolution = K4A_COLOR_RESOLUTION_720P;

  //---------------------------
};

struct Structure{
  //Structure for sensor color field
  //---------------------------

  k4n::color::Configuration config;
  k4n::structure::Data data;
  std::shared_ptr<utl::media::Image> image = std::make_shared<utl::media::Image>("Color");

  //---------------------------
};

}
