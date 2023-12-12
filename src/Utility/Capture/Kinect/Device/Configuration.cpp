#include "Configuration.h"


namespace util::kinect::configuration{

//Main function
void make_k4a_configuration(K4A_device* device){
  //---------------------------

  k4a_device_configuration_t k4a_config;
  k4a_config.color_format = device->color.config.format;
  k4a_config.color_resolution = device->color.config.enabled ? device->color.config.resolution : K4A_COLOR_RESOLUTION_OFF;
  k4a_config.depth_mode = device->depth.config.enabled ? device->depth.config.mode : K4A_DEPTH_MODE_OFF;
  k4a_config.camera_fps = device->device.fps;
  k4a_config.depth_delay_off_color_usec = device->synchro.depth_delay_off_color_us;
  k4a_config.wired_sync_mode = device->synchro.wired_sync_mode;
  k4a_config.subordinate_delay_off_master_usec = device->synchro.subordinate_delay_off_master_us;
  k4a_config.disable_streaming_indicator = device->synchro.disable_streaming_indicator;
  k4a_config.synchronized_images_only = device->synchro.synchronized_images_only;

  //---------------------------
  device->device.k4a_config = k4a_config;
}
void find_file_information(K4A_device* device, string path){
  //---------------------------

  k4a::playback playback = k4a::playback::open(path.c_str());
  k4a_record_configuration_t record_configuration = playback.get_record_configuration();

  playback.set_color_conversion(K4A_IMAGE_FORMAT_COLOR_BGRA32);
  record_configuration.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;

  //General info
  device->file.path = path;
  device->file.fps = util::kinect::configuration::find_name_from_config(record_configuration.camera_fps);
  device->file.is_depth = record_configuration.depth_track_enabled;
  device->file.is_infrared = record_configuration.ir_track_enabled;
  device->file.is_imu = record_configuration.imu_track_enabled;
  device->file.is_color = record_configuration.color_track_enabled;

  device->file.depth_mode = util::kinect::configuration::find_name_from_config(record_configuration.depth_mode);
  device->file.color_format = util::kinect::configuration::find_name_from_config(record_configuration.color_format);
  device->file.color_resolution = util::kinect::configuration::find_name_from_config(record_configuration.color_resolution);

  // Sync info
  device->file.wired_sync_mode = util::kinect::configuration::find_name_from_config(record_configuration.wired_sync_mode);
  device->synchro.depth_delay_off_color_us = record_configuration.depth_delay_off_color_usec;
  device->synchro.subordinate_delay_off_master_us = record_configuration.subordinate_delay_off_master_usec;
  device->synchro.start_timestamp_offset_us = record_configuration.start_timestamp_offset_usec;
  device->file.duration = playback.get_recording_length().count() / 1000000.0f;

  // Device info
  playback.get_tag("K4A_DEVICE_SERIAL_NUMBER", &device->file.device_serial_number);
  playback.get_tag("K4A_COLOR_FIRMWARE_VERSION", &device->file.color_firmware_version);
  playback.get_tag("K4A_DEPTH_FIRMWARE_VERSION", &device->file.depth_firmware_version);

  //---------------------------
}

//Subfunction
string find_name_from_config(k4a_wired_sync_mode_t& value){
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
string find_name_from_config(k4a_fps_t& value){
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
string find_name_from_config(k4a_depth_mode_t& value){
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
string find_name_from_config(k4a_color_resolution_t& value){
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
string find_name_from_config(k4a_image_format_t& value){
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

}
