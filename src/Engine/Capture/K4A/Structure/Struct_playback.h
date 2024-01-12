#pragma once

#include <string>


namespace k4a::stucture{

struct Playback{
  //---------------------------

  //File info
  std::string path;
  std::string filename;

  //Configuration info
  std::string fps;
  std::string depth_mode;
  std::string color_format;
  std::string color_resolution;
  std::string wired_sync_mode;
  std::string device_serial_number;
  std::string color_firmware_version;
  std::string depth_firmware_version;

  //Stream info
  bool is_color;
  bool is_depth;
  bool is_infrared;
  bool is_imu;

  //---------------------------
};

}
