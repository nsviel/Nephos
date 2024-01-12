#include "Configuration.h"


namespace k4n::config{

//Constructor / Destructor
Configuration::Configuration(){
  //---------------------------


  //---------------------------
}
Configuration::~Configuration(){}

//Main function
void Configuration::make_device_configuration(k4n::Device* k4n_device){
  //---------------------------

  k4a_device_configuration_t configuration = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
  configuration.color_format = k4n_device->color.config.format;
  configuration.color_resolution = k4n_device->color.config.enabled ? k4n_device->color.config.resolution : K4A_COLOR_RESOLUTION_OFF;
  configuration.depth_mode = k4n_device->depth.config.enabled ? k4n_device->depth.config.mode : K4A_DEPTH_MODE_OFF;
  configuration.camera_fps = k4n_device->device.fps_mode;
  configuration.depth_delay_off_color_usec = k4n_device->synchro.depth_delay_off_color_us;
  configuration.wired_sync_mode = k4n_device->synchro.wired_sync_mode;
  configuration.subordinate_delay_off_master_usec = k4n_device->synchro.subordinate_delay_off_master_us;
  configuration.disable_streaming_indicator = k4n_device->synchro.disable_streaming_indicator;
  configuration.synchronized_images_only = k4n_device->synchro.synchronized_images_only;

  //---------------------------
  k4n_device->device.configuration = configuration;
}
void Configuration::find_playback_configuration(k4n::Device* k4n_device){
  k4a_record_configuration_t configuration = k4n_device->device.playback->get_record_configuration();
  //---------------------------

 	k4a_image_format_t required_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  k4n_device->device.playback->set_color_conversion(required_format);
  configuration.color_format = required_format;

  //General info
  this->find_config_fps(k4n_device, configuration);

  k4n_device->playback.is_depth = configuration.depth_track_enabled;
  k4n_device->playback.is_infrared = configuration.ir_track_enabled;
  k4n_device->playback.is_imu = configuration.imu_track_enabled;
  k4n_device->playback.is_color = configuration.color_track_enabled;

  k4n_device->playback.depth_mode_str = find_name_from_config(configuration.depth_mode);
  k4n_device->playback.color_format_str = find_name_from_config(configuration.color_format);
  k4n_device->playback.color_resolution_str = find_name_from_config(configuration.color_resolution);

  // Sync info
  k4n_device->playback.wired_sync_mode_str = find_name_from_config(configuration.wired_sync_mode);
  k4n_device->synchro.depth_delay_off_color_us = configuration.depth_delay_off_color_usec;
  k4n_device->synchro.subordinate_delay_off_master_us = configuration.subordinate_delay_off_master_usec;
  k4n_device->synchro.start_timestamp_offset_us = configuration.start_timestamp_offset_usec;
  k4n_device->player.duration = k4n_device->device.playback->get_recording_length().count() / 1000000.0f;

  // Device info
  k4n_device->device.playback->get_tag("K4A_DEVICE_SERIAL_NUMBER", &k4n_device->playback.device_serial_number);
  k4n_device->device.playback->get_tag("K4A_COLOR_FIRMWARE_VERSION", &k4n_device->playback.color_firmware_version);
  k4n_device->device.playback->get_tag("K4A_DEPTH_FIRMWARE_VERSION", &k4n_device->playback.depth_firmware_version);

  //---------------------------
}

//Subfunction
void Configuration::find_config_fps(k4n::Device* k4n_device, k4a_record_configuration_t& configuration){
  //---------------------------



  //---------------------------
}





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
