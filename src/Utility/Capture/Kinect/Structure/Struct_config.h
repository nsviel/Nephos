#pragma once

#include <k4a/k4a.hpp>

#define VENDOR_MICROSOFT 0x045E
#define ID_RGB 0x097D
#define ID_DEPTH 0x097C


namespace util::kinect::structure{

struct Config{
  //---------------------------

  k4a_fps_t fps = K4A_FRAMES_PER_SECOND_30;
  k4a_device_configuration_t k4a_config;
  k4a_hardware_version_t version;

  //---------------------------
};

}
