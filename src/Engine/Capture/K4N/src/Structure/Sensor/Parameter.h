#pragma once

#include <Utility/Namespace.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <string>


namespace k4n::structure{

struct FPS{
  //---------------------------

  k4a_fps_t mode = K4A_FRAMES_PER_SECOND_30;
  std::string mode_str;
  int query;

  //---------------------------
};

struct Param{
  //Sensor parameters and information
  //---------------------------

  //General info
  std::string name = "";
  std::string format = "";
  std::string serial_number = "";
  utl::file::Path path;

  //General parameters
  int index = -1;
  bool data_ready = false;
  float file_size = 0;

  FPS fps;

  //K4A objects
  k4a::device device;
  k4a::playback playback;
  k4a::calibration calibration;
  k4a::transformation transformation;
  k4a_device_configuration_t configuration;
  k4a_hardware_version_t version;

  //---------------------------
};

}
