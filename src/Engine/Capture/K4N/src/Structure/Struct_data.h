#pragma once

#include <string>


namespace eng::k4n::structure{

struct Data{
  //---------------------------

  k4a::image k4a_image;
  std::string name;
  std::string format;
  uint8_t* buffer;

  int width = 0;
  int height = 0;
  int size = 0;

  float timestamp;
  float temperature = -1;
  float hovered_pixel_x;
  float hovered_pixel_y;
  float hovered_pixel_m;

  //---------------------------
};

}
