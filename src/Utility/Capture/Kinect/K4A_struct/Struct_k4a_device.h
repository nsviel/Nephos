#pragma once

#include <Utility/Capture/Kinect/K4A_struct/Namespace.h>

#include "Struct_k4a_config.h"
#include "Struct_k4a_depth.h"
#include "Struct_k4a_infrared.h"
#include "Struct_k4a_data.h"
#include "Struct_k4a_info.h"

#include <k4a/k4a.hpp>
#include <string>


struct Struct_k4a_device{
  //---------------------------

  int index;
  float temperature = 0;
  std::string serial_number;
  k4a::device* device;

  Struct_k4a_config config;
  util::kinect::structure::Color color;
  Struct_k4a_depth depth;
  Struct_k4a_infrared ir;
  Struct_k4a_data data;
  Struct_k4a_info info;

  //---------------------------
};
