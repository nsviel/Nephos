#pragma once

#include <k4a/k4a.hpp>
#include <string>


namespace util::kinect::structure{

struct Device{
  //---------------------------

  int index;
  float temperature = 0;
  std::string serial_number;
  k4a::device* device;
  bool data_ready = false;

  k4a_fps_t fps = K4A_FRAMES_PER_SECOND_30;
  k4a_device_configuration_t k4a_config;
  k4a_hardware_version_t version;

  //---------------------------
};

}
