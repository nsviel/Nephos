#include "Configuration.h"

#include <K4N/Namespace.h>


namespace k4n::config{

//Constructor / Destructor
Configuration::Configuration(){
  //---------------------------


  //---------------------------
}
Configuration::~Configuration(){}

//Capture configuration
void Configuration::make_sensor_configuration(k4n::dev::Sensor* sensor){
  k4n::dev::Master* master = sensor->master;
  //---------------------------

  k4a_device_configuration_t configuration = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
  //Field stuff
  configuration.color_format = master->config.color.format;
  configuration.color_resolution = master->config.color.resolution;
  configuration.depth_mode = master->config.depth.mode;

  //Synchro stuff
  configuration.camera_fps = master->config.fps.mode;
  configuration.depth_delay_off_color_usec = master->synchro.depth_delay_off_color_us;
  configuration.wired_sync_mode = master->synchro.wired_sync_mode;
  configuration.subordinate_delay_off_master_usec = master->synchro.subordinate_delay_off_master_us;
  configuration.disable_streaming_indicator = master->synchro.disable_streaming_indicator;
  configuration.synchronized_images_only = master->synchro.synchronized_images_only;

  //---------------------------
  sensor->param.configuration = configuration;
}
void Configuration::make_sensor_color_configuration(k4n::dev::Sensor* sensor){
  k4a::device& device = sensor->param.device;
  k4n::dev::Master* master = sensor->master;
  //---------------------------

  device.set_color_control(master->config.color.exposure.command, master->config.color.exposure.mode, master->config.color.exposure.value);
  device.set_color_control(master->config.color.white_balance.command, master->config.color.white_balance.mode, master->config.color.white_balance.value);
  device.set_color_control(master->config.color.brightness.command, master->config.color.brightness.mode, master->config.color.brightness.value);
  device.set_color_control(master->config.color.contrast.command, master->config.color.contrast.mode, master->config.color.contrast.value);
  device.set_color_control(master->config.color.saturation.command, master->config.color.saturation.mode, master->config.color.saturation.value);
  device.set_color_control(master->config.color.sharpness.command, master->config.color.sharpness.mode, master->config.color.sharpness.value);
  device.set_color_control(master->config.color.gain.command, master->config.color.gain.mode, master->config.color.gain.value);
  device.set_color_control(master->config.color.backlight_compensation.command, master->config.color.backlight_compensation.mode, master->config.color.backlight_compensation.value);
  device.set_color_control(master->config.color.power_frequency.command, master->config.color.power_frequency.mode, master->config.color.power_frequency.value);

  //---------------------------
}
void Configuration::make_master_configuration_initial(k4n::dev::Master* master){
  //---------------------------

  master->config.depth.mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
  master->config.color.format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  master->config.color.resolution = K4A_COLOR_RESOLUTION_1080P;

  master->config.fps.mode = K4A_FRAMES_PER_SECOND_30;
  master->synchro.depth_delay_off_color_us = 0;
  master->synchro.wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
  master->synchro.subordinate_delay_off_master_us = 0;
  master->synchro.disable_streaming_indicator = false;
  master->synchro.synchronized_images_only = true;

  master->config.color.exposure.value = 15625;
  master->config.color.white_balance.value = 4500;
  master->config.color.brightness.value = 128;
  master->config.color.contrast.value = 5;
  master->config.color.saturation.value = 32;
  master->config.color.sharpness.value = 2;
  master->config.color.gain.value = 0;
  master->config.color.backlight_compensation.value = 0;
  master->config.color.power_frequency.value = 2;

  //---------------------------
}

//Playback configuration
void Configuration::find_playback_configuration(k4n::dev::Sensor* sensor){
  k4a_record_configuration_t configuration = sensor->param.playback.get_record_configuration();
  //---------------------------

  this->find_config_fps(sensor, configuration);
  this->find_config_synchro(sensor, configuration);
  this->find_config_depth(sensor, configuration);
  this->find_config_color(sensor, configuration);
  this->find_config_format(sensor, configuration);
  this->find_config_device(sensor, configuration);

  //---------------------------
}
void Configuration::find_config_fps(k4n::dev::Sensor* sensor, k4a_record_configuration_t& configuration){
  //---------------------------

  switch(configuration.camera_fps){
    case K4A_FRAMES_PER_SECOND_5:{
      sensor->param.fps_mode = "5";
      break;
    }
    case K4A_FRAMES_PER_SECOND_15:{
      sensor->param.fps_mode = "15";
      break;
    }
    case K4A_FRAMES_PER_SECOND_30:{
      sensor->param.fps_mode = "30";
      break;
    }
  }

  //---------------------------
}
void Configuration::find_config_synchro(k4n::dev::Sensor* sensor, k4a_record_configuration_t& configuration){
  //---------------------------

  sensor->synchro.wired_sync_mode = configuration.wired_sync_mode;
  sensor->synchro.depth_delay_off_color_us = configuration.depth_delay_off_color_usec;
  sensor->synchro.subordinate_delay_off_master_us = configuration.subordinate_delay_off_master_usec;
  sensor->synchro.start_timestamp_offset_us = configuration.start_timestamp_offset_usec;

  switch (configuration.wired_sync_mode){
    case K4A_WIRED_SYNC_MODE_STANDALONE:{
      sensor->synchro.wired_sync_mode_str = "Standalone";
      break;
    }
    case K4A_WIRED_SYNC_MODE_MASTER:{
      sensor->synchro.wired_sync_mode_str = "Master";
      break;
    }
    case K4A_WIRED_SYNC_MODE_SUBORDINATE:{
      sensor->synchro.wired_sync_mode_str = "Subordinate";
      break;
    }
  }

  //---------------------------
}
void Configuration::find_config_depth(k4n::dev::Sensor* sensor, k4a_record_configuration_t& configuration){
  //---------------------------

  sensor->depth.config.enabled = configuration.depth_track_enabled;
  sensor->depth.config.mode = configuration.depth_mode;
  sensor->param.playback.get_tag("K4A_DEPTH_FIRMWARE_VERSION", &sensor->depth.config.firmware_version);

  switch (configuration.depth_mode){
    case K4A_DEPTH_MODE_OFF:{
      sensor->depth.config.mode_str = "Off";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_2X2BINNED:{
      sensor->depth.config.mode_str = "NFOV 2x2 binned";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_UNBINNED:{
      sensor->depth.config.mode_str = "NFOV unbinned";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_2X2BINNED:{
      sensor->depth.config.mode_str = "WFOV 2x2 binned";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_UNBINNED:{
      sensor->depth.config.mode_str = "WFOV unbinned";
      break;
    }
    case K4A_DEPTH_MODE_PASSIVE_IR:{
      sensor->depth.config.mode_str = "Passive IR";
      break;
    }
  }

  //---------------------------
}
void Configuration::find_config_color(k4n::dev::Sensor* sensor, k4a_record_configuration_t& configuration){
  //---------------------------

  //Ask for default color format
  k4a_image_format_t required_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  sensor->param.playback.set_color_conversion(required_format);
  configuration.color_format = required_format;

  sensor->color.config.enabled = configuration.color_track_enabled;
  sensor->color.config.resolution = configuration.color_resolution;
  sensor->param.playback.get_tag("K4A_COLOR_FIRMWARE_VERSION", &sensor->color.config.firmware_version);

  switch (configuration.color_resolution){
    case K4A_COLOR_RESOLUTION_OFF:{
      sensor->color.config.resolution_str = "Off";
      break;
    }
    case K4A_COLOR_RESOLUTION_720P:{
      sensor->color.config.resolution_str = "720p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1080P:{
      sensor->color.config.resolution_str = "1080p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1440P:{
      sensor->color.config.resolution_str = "1440p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1536P:{
      sensor->color.config.resolution_str = "1536p";
      break;
    }
    case K4A_COLOR_RESOLUTION_2160P:{
      sensor->color.config.resolution_str = "2160p";
      break;
    }
    case K4A_COLOR_RESOLUTION_3072P:{
      sensor->color.config.resolution_str = "3072p";
      break;
    }
  }

  //---------------------------
}
void Configuration::find_config_format(k4n::dev::Sensor* sensor, k4a_record_configuration_t& configuration){
  //---------------------------

  sensor->color.config.format = configuration.color_format;

  switch(configuration.color_format){
    case K4A_IMAGE_FORMAT_COLOR_MJPG:{
      sensor->color.config.format_str = "MJPG";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_NV12:{
      sensor->color.config.format_str = "NV12";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_YUY2:{
      sensor->color.config.format_str = "YUY2";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_BGRA32:{
      sensor->color.config.format_str = "BGRA32";
      break;
    }
    case K4A_IMAGE_FORMAT_DEPTH16:{
      sensor->color.config.format_str = "DEPTH16";
      break;
    }
    case K4A_IMAGE_FORMAT_IR16:{
      sensor->color.config.format_str = "IR16";
      break;
    }
    case K4A_IMAGE_FORMAT_CUSTOM:{
      sensor->color.config.format_str = "Custom";
      break;
    }
  }

  //---------------------------
}
void Configuration::find_config_device(k4n::dev::Sensor* sensor, k4a_record_configuration_t& configuration){
  //---------------------------

  sensor->ir.config.enabled = configuration.ir_track_enabled;
  sensor->imu.config.enabled = configuration.imu_track_enabled;
  sensor->param.playback.get_tag("K4A_DEVICE_SERIAL_NUMBER", &sensor->param.serial_number);

  //---------------------------
}


}
