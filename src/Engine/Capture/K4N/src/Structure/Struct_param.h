#pragma once

#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <string>


namespace k4n::mode{
enum Mode{
  CAPTURE = 0,
  PLAYBACK = 1,
};
}

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
  int mode = k4n::mode::PLAYBACK;
  float file_size = 0;
  FPS fps;

  std::string name = "";
  std::string format = "";
  std::string serial_number = "";
  std::string path_file = "";
  std::string path_transfo = "";

  k4a::device device;
  k4a::playback playback;
  k4a::calibration calibration;
  k4a::transformation transformation;

  k4a_device_configuration_t configuration;
  k4a_hardware_version_t version;

  //---------------------------
};

}
