#pragma once

#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <string>


namespace k4a::stucture{

struct Device{
  //---------------------------

  int index = -1;
  std::string name = "";
  std::string serial_number = "";
  bool data_ready = false;
  bool is_playback;
  float fps = 0;

  k4a::device* device;
  k4a::playback* playback;
  k4a::calibration calibration;
  k4a::transformation transformation;

  k4a_fps_t fps_mode = K4A_FRAMES_PER_SECOND_30;
  k4a_device_configuration_t k4a_config;
  k4a_hardware_version_t version;

  //---------------------------
};

}
