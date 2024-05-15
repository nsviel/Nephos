#include "Configuration.h"

#include <Kinect/Namespace.h>


namespace k4n::utils{

//Constructor / Destructor
Configuration::Configuration(){
  //---------------------------


  //---------------------------
}
Configuration::~Configuration(){}

//Configuration function
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
  configuration.wired_sync_mode = master->synchro.wired_mode;
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
  master->synchro.wired_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
  master->synchro.subordinate_delay_off_master_us = 0;
  master->synchro.disable_streaming_indicator = true;
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
void Configuration::find_playback_configuration(k4n::playback::Sensor* sensor){
  k4a_record_configuration_t configuration = sensor->playback.get_record_configuration();
  //---------------------------

  //FPS
  sensor->fps.mode_str = find_mode_fps(configuration.camera_fps);

  //Synchro
  sensor->synchro.wired_mode_str = find_mode_synchro(configuration.wired_sync_mode);
  sensor->synchro.wired_mode = configuration.wired_sync_mode;
  sensor->synchro.depth_delay_off_color_us = configuration.depth_delay_off_color_usec;
  sensor->synchro.subordinate_delay_off_master_us = configuration.subordinate_delay_off_master_usec;
  sensor->synchro.start_timestamp_offset_us = configuration.start_timestamp_offset_usec;

  //Depth
  sensor->depth.config.mode_str = find_mode_depth(configuration.depth_mode);
  sensor->depth.config.enabled = configuration.depth_track_enabled;
  sensor->depth.config.mode = configuration.depth_mode;
  sensor->playback.get_tag("K4A_DEPTH_FIRMWARE_VERSION", &sensor->depth.config.firmware_version);

  //Color
  k4a_image_format_t required_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  sensor->playback.set_color_conversion(required_format);
  configuration.color_format = required_format;

  sensor->color.config.resolution_str = find_mode_color_resolution(configuration.color_resolution);
  sensor->color.config.format_str = find_mode_color_format(configuration.color_format);
  sensor->color.config.enabled = configuration.color_track_enabled;
  sensor->color.config.resolution = configuration.color_resolution;
  sensor->color.config.format = configuration.color_format;
  sensor->playback.get_tag("K4A_COLOR_FIRMWARE_VERSION", &sensor->color.config.firmware_version);

  //Device
  sensor->ir.config.enabled = configuration.ir_track_enabled;
  sensor->imu.config.enabled = configuration.imu_track_enabled;
  sensor->playback.get_tag("K4A_DEVICE_SERIAL_NUMBER", &sensor->param.serial_number);

  //---------------------------
}
void Configuration::reset_color_configuration(k4n::dev::Sensor* sensor){
  k4n::structure::Color* color = &sensor->color;
  //---------------------------

  color->config.exposure.value = 15625;
  color->config.white_balance.value = 4500;
  color->config.brightness.value = 128;
  color->config.contrast.value = 5;
  color->config.saturation.value = 32;
  color->config.sharpness.value = 2;
  color->config.gain.value = 0;
  color->config.backlight_compensation.value = 0;
  color->config.power_frequency.value = 2;

  //---------------------------
}

//Calibration function
void Configuration::make_transformation_from_calibration(k4n::dev::Sensor* sensor){
  //---------------------------

  sensor->param.transformation = k4a::transformation(sensor->param.calibration);

  //---------------------------
}
void Configuration::make_capture_calibration(k4n::dev::Sensor* sensor){
  k4n::dev::Master* master = sensor->master;
  k4a::device& device = sensor->param.device;
  //---------------------------

  sensor->param.calibration = device.get_calibration(master->config.depth.mode, master->config.color.resolution);

  //---------------------------
}
void Configuration::find_playback_calibration(k4n::playback::Sensor* sensor){
  //---------------------------

  sensor->param.calibration = sensor->playback.get_calibration();

  //---------------------------
}

//Subfunction
string Configuration::find_mode_fps(int mode){
  string mode_str = "";
  //---------------------------

  switch(mode){
    case K4A_FRAMES_PER_SECOND_5:{
      mode_str = "5";
      break;
    }
    case K4A_FRAMES_PER_SECOND_15:{
      mode_str = "15";
      break;
    }
    case K4A_FRAMES_PER_SECOND_30:{
      mode_str = "30";
      break;
    }
  }

  //---------------------------
  return mode_str;
}
string Configuration::find_mode_synchro(int mode){
  string mode_str = "";
  //---------------------------

  switch(mode){
    case K4A_WIRED_SYNC_MODE_STANDALONE:{
      mode_str = "Standalone";
      break;
    }
    case K4A_WIRED_SYNC_MODE_MASTER:{
      mode_str = "Master";
      break;
    }
    case K4A_WIRED_SYNC_MODE_SUBORDINATE:{
      mode_str = "Subordinate";
      break;
    }
  }

  //---------------------------
  return mode_str;
}
string Configuration::find_mode_depth(int mode){
  string mode_str = "";
  //---------------------------

  switch(mode){
    case K4A_DEPTH_MODE_OFF:{
      mode_str = "Off";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_2X2BINNED:{
      mode_str = "NFOV 2x2 binned";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_UNBINNED:{
      mode_str = "NFOV unbinned";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_2X2BINNED:{
      mode_str = "WFOV 2x2 binned";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_UNBINNED:{
      mode_str = "WFOV unbinned";
      break;
    }
    case K4A_DEPTH_MODE_PASSIVE_IR:{
      mode_str = "Passive IR";
      break;
    }
  }

  //---------------------------
  return mode_str;
}
string Configuration::find_mode_color_resolution(int mode){
  string mode_str = "";
  //---------------------------

  switch(mode){
    case K4A_COLOR_RESOLUTION_OFF:{
      mode_str = "Off";
      break;
    }
    case K4A_COLOR_RESOLUTION_720P:{
      mode_str = "720p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1080P:{
      mode_str = "1080p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1440P:{
      mode_str = "1440p";
      break;
    }
    case K4A_COLOR_RESOLUTION_1536P:{
      mode_str = "1536p";
      break;
    }
    case K4A_COLOR_RESOLUTION_2160P:{
      mode_str = "2160p";
      break;
    }
    case K4A_COLOR_RESOLUTION_3072P:{
      mode_str = "3072p";
      break;
    }
  }

  //---------------------------
  return mode_str;
}
string Configuration::find_mode_color_format(int mode){
  string mode_str = "";
  //---------------------------

  switch(mode){
    case K4A_IMAGE_FORMAT_COLOR_MJPG:{
      mode_str = "MJPG";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_NV12:{
      mode_str = "NV12";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_YUY2:{
      mode_str = "YUY2";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_BGRA32:{
      mode_str = "BGRA32";
      break;
    }
    case K4A_IMAGE_FORMAT_DEPTH16:{
      mode_str = "DEPTH16";
      break;
    }
    case K4A_IMAGE_FORMAT_IR16:{
      mode_str = "IR16";
      break;
    }
    case K4A_IMAGE_FORMAT_CUSTOM:{
      mode_str = "Custom";
      break;
    }
  }

  //---------------------------
  return mode_str;
}


}
