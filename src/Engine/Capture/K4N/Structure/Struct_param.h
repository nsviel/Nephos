#pragma once

#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <string>


namespace k4n::structure{

struct FPS{
  //---------------------------

  k4a_fps_t mode = K4A_FRAMES_PER_SECOND_30;
  std::string mode_str;
  float current = 0;
  int query;

  //---------------------------
};

struct Param{
  //---------------------------

  int index = -1;
  bool data_ready = false;
  bool is_playback;
  FPS fps;

  std::string name = "";
  std::string serial_number = "";
  std::string file_path = "";
  std::string file_name = "";
  std::string file_format = "";

  k4a::device* device;
  k4a::playback* playback;
  k4a::calibration calibration;
  k4a::transformation transformation;

  k4a_device_configuration_t configuration;
  k4a_hardware_version_t version;

  //---------------------------
};

}
