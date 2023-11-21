#ifndef STRUCT_K4A_DEVICE_H
#define STRUCT_K4A_DEVICE_H

#include "Struct_k4a_config.h"
#include "Struct_k4a_color.h"
#include "Struct_k4a_depth.h"
#include "Struct_k4a_data.h"

#include <k4a/k4a.hpp>
#include <string>


struct Struct_k4a_device{
  //---------------------------

  int index;
  bool is_capturing = false;
  float temperature = 0;
  std::string serial_number;
  k4a::capture* capture = nullptr;
  k4a::device* device = nullptr;

  Struct_k4a_config config;
  Struct_k4a_color color;
  Struct_k4a_depth depth;
  Struct_k4a_data data;

  //---------------------------
};



#endif
