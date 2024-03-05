#pragma once

#include <string>


namespace k4n::structure{

struct Data{
  //---------------------------

  k4a::image k4a_image;
  std::string name = "";
  std::string format = "";
  uint8_t* buffer = nullptr;

  int width = 0;
  int height = 0;
  int size = 0;
  k4a_calibration_type_t calibration_type;

  float timestamp = -1;
  float temperature = -1;
  float hovered_pixel_x;
  float hovered_pixel_y;
  float hovered_pixel_m;

  //---------------------------
};

}
