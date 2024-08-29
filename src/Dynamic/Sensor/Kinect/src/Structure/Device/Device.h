#pragma once

#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <k4arecord/record.hpp>
#include <string>


namespace k4n::device{

enum Mode{
  CAPTURE = 0,
  PLAYBACK = 1,
};

struct Structure{
  //Sensor parameters and information
  //---------------------------

  //General parameters
  int index = -1;
  int mode = k4n::device::PLAYBACK;

  //K4A device related objects
  k4a::device handle;
  k4a::calibration calibration;
  k4a::transformation transformation;
  std::shared_ptr<k4a::capture> capture;
  k4a::record recorder;
  k4a::playback playback;
  k4a_device_configuration_t configuration = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
  k4a_hardware_version_t version = {0};

  std::vector<uint16_t> table_xy;

  //---------------------------
};

}
