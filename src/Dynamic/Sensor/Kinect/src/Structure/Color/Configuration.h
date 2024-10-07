#pragma once

#include <k4a/k4a.hpp>


namespace k4n::str::color{

struct Configuration{
  //---------------------------

  k4a_image_format_t format = K4A_IMAGE_FORMAT_COLOR_YUY2;
  k4a_color_resolution_t resolution = K4A_COLOR_RESOLUTION_720P;
  bool enabled = true;

  //---------------------------
};

}
