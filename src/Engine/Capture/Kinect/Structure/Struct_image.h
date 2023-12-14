#pragma once

#include <string>


namespace eng::kinect::structure{

struct Image{
  //---------------------------

  k4a::image image;
  std::string name;
  std::string format;
  std::vector<uint8_t> data;
  
  int width;
  int height;

  float timestamp;
  float temperature = -1;
  float hovered_pixel_x;
  float hovered_pixel_y;
  float hovered_pixel_m;

  //---------------------------
};

}
