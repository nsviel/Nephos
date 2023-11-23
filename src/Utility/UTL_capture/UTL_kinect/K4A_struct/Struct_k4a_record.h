#ifndef STRUCT_K4A_RECORD_H
#define STRUCT_K4A_RECORD_H

#include <k4a/k4a.hpp>
#include <string>


struct Struct_k4a_record{
  //---------------------------

  //Objects
  k4a_record_configuration_t record_configuration;

  //Info
  std::string path;
  std::string info_fps;
  std::string info_depth_mode;
  std::string info_color_format;
  std::string info_color_resolution;
  std::string info_wired_sync_mode;
  std::string info_device_serial_number;
  std::string info_color_firmware_version;
  std::string info_depth_firmware_version;
  uint32_t info_depth_delay_off_color_us;
  uint32_t info_subordinate_delay_off_master;
  uint32_t info_start_timestamp_offset_us;
  uint64_t info_recording_lenght_us;
  bool is_color;
  bool is_depth;
  bool is_infrared;
  bool is_imu;

  //---------------------------
};



#endif
