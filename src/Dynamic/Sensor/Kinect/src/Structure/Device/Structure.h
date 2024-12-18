#pragma once

#include <Kinect/src/Structure/Device/Firmware.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <k4arecord/record.hpp>
#include <memory>
#include <string>


namespace k4n::str::device{

struct Structure{
  //Sensor parameters and information
  //---------------------------

  //General parameters
  int index = -1;
  std::shared_ptr<k4a::capture> capture = std::make_shared<k4a::capture>();
  k4n::str::device::Firmware firmware;

  //K4A device related objects
  k4a_device_configuration_t configuration = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
  k4a_calibration_type_t calibration_type;
  k4a::device handle;
  k4a::calibration calibration;
  k4a::transformation transformation;
  k4a::record recorder;
  k4a::playback playback;

  //---------------------------
};

}
