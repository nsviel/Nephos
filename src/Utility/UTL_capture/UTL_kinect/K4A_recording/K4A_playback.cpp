#include "K4A_playback.h"

#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <UTL_capture/UTL_kinect/Struct_kinect.h>


//Constructor / Destructor
K4A_playback::K4A_playback(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;
  this->k4a_device = new K4A_device(struct_kinect);

  //---------------------------
}
K4A_playback::~K4A_playback(){}

//Main function
void K4A_playback::find_file_information(string path){
  //---------------------------

  k4a::playback recording = k4a::playback::open(path.c_str());
  k4a_record_configuration_t record_configuration = recording.get_record_configuration();

  recording.set_color_conversion(K4A_IMAGE_FORMAT_COLOR_BGRA32);
  record_configuration.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;

  //General info
  struct_info.file_path = path;
  struct_info.info_fps = k4a_device->find_name_from_config(record_configuration.camera_fps);
  struct_info.is_depth = record_configuration.depth_track_enabled;
  struct_info.is_infrared = record_configuration.ir_track_enabled;
  struct_info.is_imu = record_configuration.imu_track_enabled;
  struct_info.is_color = record_configuration.color_track_enabled;

  struct_info.info_depth_mode = k4a_device->find_name_from_config(record_configuration.depth_mode);
  struct_info.info_color_format = k4a_device->find_name_from_config(record_configuration.color_format);
  struct_info.info_color_resolution = k4a_device->find_name_from_config(record_configuration.color_resolution);

  // Sync info
  struct_info.info_wired_sync_mode = k4a_device->find_name_from_config(record_configuration.wired_sync_mode);
  struct_info.depth_delay_off_color_us = record_configuration.depth_delay_off_color_usec;
  struct_info.subordinate_delay_off_master_us = record_configuration.subordinate_delay_off_master_usec;
  struct_info.start_timestamp_offset_us = record_configuration.start_timestamp_offset_usec;
  struct_info.file_duration = static_cast<uint64_t>(recording.get_recording_length().count());

  // Device info
  recording.get_tag("K4A_DEVICE_SERIAL_NUMBER", &struct_info.info_device_serial_number);
  recording.get_tag("K4A_COLOR_FIRMWARE_VERSION", &struct_info.info_color_firmware_version);
  recording.get_tag("K4A_DEPTH_FIRMWARE_VERSION", &struct_info.info_depth_firmware_version);

  //---------------------------
}
