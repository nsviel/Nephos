#include "K4A_configuration.h"

#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <UTL_capture/UTL_kinect/Struct_kinect.h>


//Constructor / Destructor
K4A_configuration::K4A_configuration(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;
  this->k4a_device = new K4A_device();

  //---------------------------
}
K4A_configuration::~K4A_configuration(){}

//Main function
void K4A_configuration::find_file_information(string path){
  //---------------------------

  k4a::playback recording = k4a::playback::open(path.c_str());
  k4a_record_configuration_t record_configuration = recording.get_record_configuration();

  recording.set_color_conversion(K4A_IMAGE_FORMAT_COLOR_BGRA32);
  record_configuration.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;

  //General info
  struct_info.file_path = path;
  struct_info.info_fps = this->find_name_from_config(record_configuration.camera_fps);
  struct_info.is_depth = record_configuration.depth_track_enabled;
  struct_info.is_infrared = record_configuration.ir_track_enabled;
  struct_info.is_imu = record_configuration.imu_track_enabled;
  struct_info.is_color = record_configuration.color_track_enabled;

  struct_info.info_depth_mode = this->find_name_from_config(record_configuration.depth_mode);
  struct_info.info_color_format = this->find_name_from_config(record_configuration.color_format);
  struct_info.info_color_resolution = this->find_name_from_config(record_configuration.color_resolution);

  // Sync info
  struct_info.info_wired_sync_mode = this->find_name_from_config(record_configuration.wired_sync_mode);
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
string K4A_configuration::find_name_from_config(k4a_wired_sync_mode_t& value){
  string name = "(None)";
  //---------------------------

  switch (value){
    case K4A_WIRED_SYNC_MODE_STANDALONE:{
      name = "K4A_WIRED_SYNC_MODE_STANDALONE";
      break;
    }
    case K4A_WIRED_SYNC_MODE_MASTER:{
      name = "K4A_WIRED_SYNC_MODE_MASTER";
      break;
    }
    case K4A_WIRED_SYNC_MODE_SUBORDINATE:{
      name = "K4A_WIRED_SYNC_MODE_SUBORDINATE";
      break;
    }
  }

  //---------------------------
  return name;
}
string K4A_configuration::find_name_from_config(k4a_fps_t& value){
  string name = "(None)";
  //---------------------------

  switch (value){
    case K4A_FRAMES_PER_SECOND_5:{
      name = "K4A_FRAMES_PER_SECOND_5";
      break;
    }
    case K4A_FRAMES_PER_SECOND_15:{
      name = "K4A_FRAMES_PER_SECOND_15";
      break;
    }
    case K4A_FRAMES_PER_SECOND_30:{
      name = "K4A_FRAMES_PER_SECOND_30";
      break;
    }
  }

  //---------------------------
  return name;
}
string K4A_configuration::find_name_from_config(k4a_depth_mode_t& value){
  string name = "(None)";
  //---------------------------

  switch (value){
    case K4A_DEPTH_MODE_OFF:{
      name = "K4A_DEPTH_MODE_OFF";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_2X2BINNED:{
      name = "K4A_DEPTH_MODE_NFOV_2X2BINNED";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_UNBINNED:{
      name = "K4A_DEPTH_MODE_NFOV_UNBINNED";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_2X2BINNED:{
      name = "K4A_DEPTH_MODE_WFOV_2X2BINNED";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_UNBINNED:{
      name = "K4A_DEPTH_MODE_WFOV_UNBINNED";
      break;
    }
    case K4A_DEPTH_MODE_PASSIVE_IR:{
      name = "K4A_DEPTH_MODE_PASSIVE_IR";
      break;
    }
  }

  //---------------------------
  return name;
}
string K4A_configuration::find_name_from_config(k4a_color_resolution_t& value){
  string name = "(None)";
  //---------------------------

  switch (value){
    case K4A_COLOR_RESOLUTION_OFF:{
      name = "K4A_COLOR_RESOLUTION_OFF";
      break;
    }
    case K4A_COLOR_RESOLUTION_720P:{
      name = "K4A_COLOR_RESOLUTION_720P";
      break;
    }
    case K4A_COLOR_RESOLUTION_1080P:{
      name = "K4A_COLOR_RESOLUTION_1080P";
      break;
    }
    case K4A_COLOR_RESOLUTION_1440P:{
      name = "K4A_COLOR_RESOLUTION_1440P";
      break;
    }
    case K4A_COLOR_RESOLUTION_1536P:{
      name = "K4A_COLOR_RESOLUTION_1536P";
      break;
    }
    case K4A_COLOR_RESOLUTION_2160P:{
      name = "K4A_COLOR_RESOLUTION_2160P";
      break;
    }
    case K4A_COLOR_RESOLUTION_3072P:{
      name = "K4A_COLOR_RESOLUTION_3072P";
      break;
    }
  }

  //---------------------------
  return name;
}
string K4A_configuration::find_name_from_config(k4a_image_format_t& value){
  string name = "(None)";
  //---------------------------

  switch (value){
    case K4A_IMAGE_FORMAT_COLOR_MJPG:{
      name = "K4A_IMAGE_FORMAT_COLOR_MJPG";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_NV12:{
      name = "K4A_IMAGE_FORMAT_COLOR_NV12";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_YUY2:{
      name = "K4A_IMAGE_FORMAT_COLOR_YUY2";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_BGRA32:{
      name = "K4A_IMAGE_FORMAT_COLOR_BGRA32";
      break;
    }
    case K4A_IMAGE_FORMAT_DEPTH16:{
      name = "K4A_IMAGE_FORMAT_DEPTH16";
      break;
    }
    case K4A_IMAGE_FORMAT_IR16:{
      name = "K4A_IMAGE_FORMAT_IR16";
      break;
    }
    case K4A_IMAGE_FORMAT_CUSTOM:{
      name = "K4A_IMAGE_FORMAT_CUSTOM";
      break;
    }
  }

  //---------------------------
  return name;
}
