#pragma once

#include <string>


namespace eng::kinect::structure{

struct File{
  //---------------------------

  //File info
  std::string path;
  float duration;
  float ts_beg;
  float ts_end;
  float ts_cur;

  //General info
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
