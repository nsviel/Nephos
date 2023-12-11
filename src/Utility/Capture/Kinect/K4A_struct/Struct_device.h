#pragma once

#include <Utility/Capture/Kinect/K4A_struct/Namespace.h>
#include <k4a/k4a.hpp>
#include <string>


namespace util::kinect::structure{

struct Device{
  //---------------------------

  int index;
  float temperature = 0;
  std::string serial_number;
  k4a::device* device;

  util::kinect::structure::Config config;
  util::kinect::structure::Color color;
  util::kinect::structure::Depth depth;
  util::kinect::structure::Infrared ir;
  util::kinect::structure::Data data;
  util::kinect::structure::Info info;

  //---------------------------
};

}
