#pragma once

#include <k4a/k4a.hpp>
#include <string>


namespace util::kinect::structure{

struct Device{
  //---------------------------

  int index;
  std::string serial_number;
  bool data_ready = false;
  bool is_virtual;
  float fps;

  k4a::device* device;
  k4a::calibration calibration;
  k4a::transformation transformation;

  k4a_fps_t fps_mode = K4A_FRAMES_PER_SECOND_30;
  k4a_device_configuration_t k4a_config;
  k4a_hardware_version_t version;

  //---------------------------
};

}
