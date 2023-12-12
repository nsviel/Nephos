#pragma once

#include <string>


namespace util::kinect::structure{

struct Image{
  //---------------------------

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

  //---------------------------
};

}
