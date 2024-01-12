#pragma once

#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <string>


namespace k4n::structure{

struct Device{
  //---------------------------

  int index = -1;
  bool data_ready = false;
  bool is_playback;

  std::string name = "";
  std::string serial_number = "";

  k4a::device* device;
  k4a::playback* playback;
  k4a::calibration calibration;
  k4a::transformation transformation;

  k4a_device_configuration_t configuration;
  k4a_hardware_version_t version;

  //FPS
  k4a_fps_t fps_mode = K4A_FRAMES_PER_SECOND_30;
  std::string fps_mode_str;
  float fps_current = 0;
  int fps_query;

  //---------------------------
};

}
