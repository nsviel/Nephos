#pragma once

#include <k4a/k4a.hpp>
#include <string>


namespace k4n::structure{

struct Data{
  //Generic structure for sensor field data
  //---------------------------

  //Sensor field info
  std::string name = "";
  std::string format = "";

  //Sensor field data
  k4a::image k4a_image;
  int width = 0;
  int height = 0;
  int size = 0;
  uint8_t* buffer = nullptr;
  k4a_calibration_type_t calibration_type;

  //Specific sensor field info
  float fps = 0;
  float timestamp = -1;
  float temperature = -1;
  float hovered_pixel_x;
  float hovered_pixel_y;
  float hovered_pixel_m;

  //---------------------------
};

}
