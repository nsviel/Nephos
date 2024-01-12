#include "Configuration.h"


namespace k4n::config{

//Constructor / Destructor
Configuration::Configuration(){
  //---------------------------


  //---------------------------
}
Configuration::~Configuration(){}

//Main function
void Configuration::init_device_calibration(k4n::device::Device* k4a_device){
  //---------------------------

  k4a_device->device.calibration = k4a_device->device.device->get_calibration(k4a_device->depth.config.mode, k4a_device->color.config.resolution);

  //---------------------------
}
void Configuration::init_playback_calibration(k4n::device::Device* k4a_device){
  //---------------------------

  k4a_device->device.calibration = k4a_device->device.playback->get_calibration();

  //---------------------------
}
void Configuration::init_device_transformation(k4n::device::Device* k4a_device){
  //---------------------------

  k4a_device->device.transformation = k4a::transformation(k4a_device->device.calibration);

  //---------------------------
}
void Configuration::make_k4a_configuration(k4n::device::Device* k4a_device){
  //---------------------------

  k4a_device_configuration_t k4a_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
  k4a_config.color_format = k4a_device->color.config.format;
  k4a_config.color_resolution = k4a_device->color.config.enabled ? k4a_device->color.config.resolution : K4A_COLOR_RESOLUTION_OFF;
  k4a_config.depth_mode = k4a_device->depth.config.enabled ? k4a_device->depth.config.mode : K4A_DEPTH_MODE_OFF;
  k4a_config.camera_fps = k4a_device->device.fps_mode;
  k4a_config.depth_delay_off_color_usec = k4a_device->synchro.depth_delay_off_color_us;
  k4a_config.wired_sync_mode = k4a_device->synchro.wired_sync_mode;
  k4a_config.subordinate_delay_off_master_usec = k4a_device->synchro.subordinate_delay_off_master_us;
  k4a_config.disable_streaming_indicator = k4a_device->synchro.disable_streaming_indicator;
  k4a_config.synchronized_images_only = k4a_device->synchro.synchronized_images_only;

  //---------------------------
  k4a_device->device.k4a_config = k4a_config;
}
void Configuration::find_file_information(k4n::device::Device* k4a_device){
  //---------------------------

  k4a::playback playback = k4a::playback::open(k4a_device->playback.path.c_str());
  k4a_record_configuration_t record_configuration = playback.get_record_configuration();

  playback.set_color_conversion(K4A_IMAGE_FORMAT_COLOR_BGRA32);
  record_configuration.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;

  //General info
  k4a_device->playback.fps = find_name_from_config(record_configuration.camera_fps);
  k4a_device->playback.is_depth = record_configuration.depth_track_enabled;
  k4a_device->playback.is_infrared = record_configuration.ir_track_enabled;
  k4a_device->playback.is_imu = record_configuration.imu_track_enabled;
  k4a_device->playback.is_color = record_configuration.color_track_enabled;

  k4a_device->playback.depth_mode = find_name_from_config(record_configuration.depth_mode);
  k4a_device->playback.color_format = find_name_from_config(record_configuration.color_format);
  k4a_device->playback.color_resolution = find_name_from_config(record_configuration.color_resolution);

  // Sync info
  k4a_device->playback.wired_sync_mode = find_name_from_config(record_configuration.wired_sync_mode);
  k4a_device->synchro.depth_delay_off_color_us = record_configuration.depth_delay_off_color_usec;
  k4a_device->synchro.subordinate_delay_off_master_us = record_configuration.subordinate_delay_off_master_usec;
  k4a_device->synchro.start_timestamp_offset_us = record_configuration.start_timestamp_offset_usec;
  k4a_device->player.duration = playback.get_recording_length().count() / 1000000.0f;

  // Device info
  playback.get_tag("K4A_DEVICE_SERIAL_NUMBER", &k4a_device->playback.device_serial_number);
  playback.get_tag("K4A_COLOR_FIRMWARE_VERSION", &k4a_device->playback.color_firmware_version);
  playback.get_tag("K4A_DEPTH_FIRMWARE_VERSION", &k4a_device->playback.depth_firmware_version);

  //---------------------------
}

//Subfunction
string Configuration::find_name_from_config(k4a_wired_sync_mode_t& value){
  string name = "(None)";
  //---------------------------

  switch (value){
    case K4A_WIRED_SYNC_MODE_STANDALONE:{
      name = "Standalone";
      break;
    }
    case K4A_WIRED_SYNC_MODE_MASTER:{
      name = "Master";
      break;
    }
    case K4A_WIRED_SYNC_MODE_SUBORDINATE:{
      name = "Subordinate";
      break;
    }
  }

  //---------------------------
  return name;
}
string Configuration::find_name_from_config(k4a_fps_t& value){
  string name = "(None)";
  //---------------------------

  switch (value){
    case K4A_FRAMES_PER_SECOND_5:{
      name = "5 fps";
      break;
    }
    case K4A_FRAMES_PER_SECOND_15:{
      name = "15 fps";
      break;
    }
    case K4A_FRAMES_PER_SECOND_30:{
      name = "30 fps";
      break;
    }
  }

  //---------------------------
  return name;
}
string Configuration::find_name_from_config(k4a_depth_mode_t& value){
  string name = "(None)";
  //---------------------------

  switch (value){
    case K4A_DEPTH_MODE_OFF:{
      name = "Off";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_2X2BINNED:{
      name = "NFOV 2x2 binned";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_UNBINNED:{
      name = "NFOV unbinned";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_2X2BINNED:{
      name = "WFOV 2x2 binned";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_UNBINNED:{
      name = "WFOV unbinned";
      break;
    }
    case K4A_DEPTH_MODE_PASSIVE_IR:{
      name = "Passive IR";
      break;
    }
  }

  //---------------------------
  return name;
}
string Configuration::find_name_from_config(k4a_color_resolution_t& value){
  string name = "(None)";
  //---------------------------

  switch (value){
    case K4A_COLOR_RESOLUTION_OFF:{
      name = "Off";
      break;
    }
    case K4A_COLOR_RESOLUTION_720P:{
      name = "720p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1080P:{
      name = "1080p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1440P:{
      name = "1440p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1536P:{
      name = "1536p";
      break;
    }
    case K4A_COLOR_RESOLUTION_2160P:{
      name = "2160p";
      break;
    }
    case K4A_COLOR_RESOLUTION_3072P:{
      name = "3072p";
      break;
    }
  }

  //---------------------------
  return name;
}
string Configuration::find_name_from_config(k4a_image_format_t& value){
  string name = "(None)";
  //---------------------------

  switch (value){
    case K4A_IMAGE_FORMAT_COLOR_MJPG:{
      name = "MJPG";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_NV12:{
      name = "NV12";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_YUY2:{
      name = "YUY2";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_BGRA32:{
      name = "BGRA32";
      break;
    }
    case K4A_IMAGE_FORMAT_DEPTH16:{
      name = "DEPTH16";
      break;
    }
    case K4A_IMAGE_FORMAT_IR16:{
      name = "IR16";
      break;
    }
    case K4A_IMAGE_FORMAT_CUSTOM:{
      name = "Custom";
      break;
    }
  }

  //---------------------------
  return name;
}

}
