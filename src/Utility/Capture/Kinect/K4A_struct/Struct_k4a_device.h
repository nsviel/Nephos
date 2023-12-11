#pragma once

#include <Utility/Capture/Kinect/K4A_struct/Namespace.h>

#include "Config.h"
#include "Depth.h"
#include "Struct_k4a_infrared.h"
#include "Data.h"
#include "Struct_k4a_info.h"

#include <k4a/k4a.hpp>
#include <string>


struct Struct_k4a_device{
  //---------------------------

  int index;
  float temperature = 0;
  std::string serial_number;
  k4a::device* device;

  Config config;
  util::kinect::structure::Color color;
  Depth depth;
  Struct_k4a_infrared ir;
  Data data;
  Struct_k4a_info info;

  //---------------------------
};
