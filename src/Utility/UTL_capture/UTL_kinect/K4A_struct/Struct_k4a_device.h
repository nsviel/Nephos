#ifndef STRUCT_K4A_DEVICE_H
#define STRUCT_K4A_DEVICE_H

#include "Struct_k4a_config.h"
#include "Struct_k4a_color.h"
#include "Struct_k4a_depth.h"

#include <k4a/k4a.hpp>
#include <string>


struct Struct_k4a_device{
  //---------------------------

  int index;
  std::string serial_number;
  k4a::capture* k4a_capture;
  k4a::device* k4a_device;

  Struct_k4a_config config;
  Struct_k4a_color color;
  Struct_k4a_depth depth;

  //---------------------------
};



#endif
