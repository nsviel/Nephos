#pragma once

#include <string>


namespace util::kinect::structure{

struct K4A_image{
  //---------------------------

  std::string name;
  std::string format;

  int width;
  int height;
  uint8_t* buffer;
  size_t size;
  float timestamp;

  //---------------------------
};

struct Data{
  //---------------------------

  util::kinect::structure::K4A_image color;
  util::kinect::structure::K4A_image depth;
  util::kinect::structure::K4A_image ir;
  bool data_ready = false;

  //---------------------------
};

}
