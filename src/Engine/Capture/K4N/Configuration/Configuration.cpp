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
  this->find_config_synchro(k4n_device, configuration);
  this->find_config_depth(k4n_device, configuration);
  this->find_config_color(k4n_device, configuration);
  this->find_config_format(k4n_device, configuration);
  this->find_config_device(k4n_device, configuration);

  //---------------------------
}

//Subfunction
void Configuration::find_config_fps(k4n::Device* k4n_device, k4a_record_configuration_t& configuration){
  //---------------------------

  k4n_device->device.fps_mode = configuration.camera_fps;
  switch(configuration.camera_fps){
    case K4A_FRAMES_PER_SECOND_5:{
      k4n_device->device.fps = 5;
      break;
    }
    case K4A_FRAMES_PER_SECOND_15:{
      k4n_device->device.fps = 15;
      break;
    }
    case K4A_FRAMES_PER_SECOND_30:{
      k4n_device->device.fps = 30;
      break;
    }
  }

  //---------------------------
}
void Configuration::find_config_synchro(k4n::Device* k4n_device, k4a_record_configuration_t& configuration){
  //---------------------------

  k4n_device->synchro.wired_sync_mode = configuration.wired_sync_mode;
  k4n_device->synchro.depth_delay_off_color_us = configuration.depth_delay_off_color_usec;
  k4n_device->synchro.subordinate_delay_off_master_us = configuration.subordinate_delay_off_master_usec;
  k4n_device->synchro.start_timestamp_offset_us = configuration.start_timestamp_offset_usec;

  switch (configuration.wired_sync_mode){
    case K4A_WIRED_SYNC_MODE_STANDALONE:{
      k4n_device->synchro.wired_sync_mode_str = "Standalone";
      break;
    }
    case K4A_WIRED_SYNC_MODE_MASTER:{
      k4n_device->synchro.wired_sync_mode_str = "Master";
      break;
    }
    case K4A_WIRED_SYNC_MODE_SUBORDINATE:{
      k4n_device->synchro.wired_sync_mode_str = "Subordinate";
      break;
    }
  }

  //---------------------------
}
void Configuration::find_config_depth(k4n::Device* k4n_device, k4a_record_configuration_t& configuration){
  //---------------------------

  k4n_device->depth.config.enabled = configuration.depth_track_enabled;
  k4n_device->depth.config.mode = configuration.depth_mode;
  k4n_device->device.playback->get_tag("K4A_DEPTH_FIRMWARE_VERSION", &k4n_device->depth.config.firmware_version);

  switch (configuration.depth_mode){
    case K4A_DEPTH_MODE_OFF:{
      k4n_device->depth.config.mode_str = "Off";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_2X2BINNED:{
      k4n_device->depth.config.mode_str = "NFOV 2x2 binned";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_UNBINNED:{
      k4n_device->depth.config.mode_str = "NFOV unbinned";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_2X2BINNED:{
      k4n_device->depth.config.mode_str = "WFOV 2x2 binned";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_UNBINNED:{
      k4n_device->depth.config.mode_str = "WFOV unbinned";
      break;
    }
    case K4A_DEPTH_MODE_PASSIVE_IR:{
      k4n_device->depth.config.mode_str = "Passive IR";
      break;
    }
  }

  //---------------------------
}
void Configuration::find_config_color(k4n::Device* k4n_device, k4a_record_configuration_t& configuration){
  //---------------------------

  k4n_device->color.config.enabled = configuration.color_track_enabled;
  k4n_device->color.config.resolution = configuration.color_resolution;
  k4n_device->device.playback->get_tag("K4A_COLOR_FIRMWARE_VERSION", &k4n_device->color.config.firmware_version);

  switch (configuration.color_resolution){
    case K4A_COLOR_RESOLUTION_OFF:{
      k4n_device->color.config.resolution_str = "Off";
      break;
    }
    case K4A_COLOR_RESOLUTION_720P:{
      k4n_device->color.config.resolution_str = "720p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1080P:{
      k4n_device->color.config.resolution_str = "1080p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1440P:{
      k4n_device->color.config.resolution_str = "1440p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1536P:{
      k4n_device->color.config.resolution_str = "1536p";
      break;
    }
    case K4A_COLOR_RESOLUTION_2160P:{
      k4n_device->color.config.resolution_str = "2160p";
      break;
    }
    case K4A_COLOR_RESOLUTION_3072P:{
      k4n_device->color.config.resolution_str = "3072p";
      break;
    }
  }

  //---------------------------
}
void Configuration::find_config_format(k4n::Device* k4n_device, k4a_record_configuration_t& configuration){
  //---------------------------

  k4n_device->color.config.format = configuration.color_format;

  switch(configuration.color_format){
    case K4A_IMAGE_FORMAT_COLOR_MJPG:{
      k4n_device->color.config.format_str = "MJPG";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_NV12:{
      k4n_device->color.config.format_str = "NV12";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_YUY2:{
      k4n_device->color.config.format_str = "YUY2";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_BGRA32:{
      k4n_device->color.config.format_str = "BGRA32";
      break;
    }
    case K4A_IMAGE_FORMAT_DEPTH16:{
      k4n_device->color.config.format_str = "DEPTH16";
      break;
    }
    case K4A_IMAGE_FORMAT_IR16:{
      k4n_device->color.config.format_str = "IR16";
      break;
    }
    case K4A_IMAGE_FORMAT_CUSTOM:{
      k4n_device->color.config.format_str = "Custom";
      break;
    }
  }

  //---------------------------
}
void Configuration::find_config_device(k4n::Device* k4n_device, k4a_record_configuration_t& configuration){
  //---------------------------

  k4n_device->ir.config.enabled = configuration.ir_track_enabled;
  k4n_device->imu.config.enabled = configuration.imu_track_enabled;
  k4n_device->player.duration = k4n_device->device.playback->get_recording_length().count() / 1000000.0f;
  k4n_device->device.playback->get_tag("K4A_DEVICE_SERIAL_NUMBER", &k4n_device->device.serial_number);

  //---------------------------
}


}
