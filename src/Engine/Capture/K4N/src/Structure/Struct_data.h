#pragma once

#include <string>


namespace eng::k4n::structure{

struct Data{
  //---------------------------

  k4a::image k4a_image;
  std::string name;
  std::string format;
  std::vector<uint8_t> buffer_vec;
  uint8_t* buffer_raw;

  int width;
  int height;
  int size;

  float timestamp;
  float temperature = -1;
  float hovered_pixel_x;
  float hovered_pixel_y;
  float hovered_pixel_m;

  //---------------------------
};

}
