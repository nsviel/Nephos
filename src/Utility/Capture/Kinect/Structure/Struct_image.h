#pragma once

#include <string>


namespace util::kinect::structure{

struct Image{
  //---------------------------

  std::string format;

  int width;
  int height;
  uint8_t* buffer;
  size_t size;
  float timestamp;

  //---------------------------
};

}
