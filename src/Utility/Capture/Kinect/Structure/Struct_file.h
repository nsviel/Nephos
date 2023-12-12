#pragma once

#include <string>


namespace util::kinect::structure{

struct File{
  //---------------------------

  //File info
  std::string file_path;
  float file_duration;
  float ts_beg;
  float ts_end;
  float ts_cur;

  //General info
  std::string info_fps;
  std::string info_depth_mode;
  std::string info_color_format;
  std::string info_color_resolution;
  std::string info_wired_sync_mode;
  std::string info_device_serial_number;
  std::string info_color_firmware_version;
  std::string info_depth_firmware_version;

  //Stream info
  bool is_color;
  bool is_depth;
  bool is_infrared;
  bool is_imu;

  //---------------------------
};

}
