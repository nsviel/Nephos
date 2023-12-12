#pragma once

#include <string>


namespace eng::kinect::structure{

struct Image{
  //---------------------------

  k4a::image image;
  std::string name;
  std::string format;
  int width;
  int height;
  uint8_t* buffer;
  size_t size;
  float timestamp;
  float temperature = -1;
  float hovered_pixel_x;
  float hovered_pixel_y;
  float hovered_pixel_m;

  //---------------------------
};

}
