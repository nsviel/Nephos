#pragma once

#include <Utility/Namespace.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <k4arecord/record.hpp>
#include <string>


namespace k4n::device{

struct Structure{
  //Sensor parameters and information
  //---------------------------

  //General parameters
  int index = -1;
  int index_cloud = 0;
  bool data_ready = false;
  bool is_capturing = false;
  float file_size = 0;
  std::string serial_number = "";

  //K4A objects
  k4a::device handle;
  k4a::calibration calibration;
  k4a::transformation transformation;
  k4a::capture* capture;
  k4a::record recorder;
  k4a_device_configuration_t configuration = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
  k4a_hardware_version_t version = {0};

  //---------------------------
};

}
