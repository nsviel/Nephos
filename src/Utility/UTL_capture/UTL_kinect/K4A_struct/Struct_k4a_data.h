#pragma once

#include <k4a/k4a.hpp>
#include <string>


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

struct Struct_k4a_data{
  //---------------------------

  K4A_image color;
  K4A_image depth;
  K4A_image ir;
  bool data_ready = false;

  //---------------------------
};
