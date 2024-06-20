#include "Configuration.h"

#include <Kinect/Namespace.h>


namespace k4n::utils{

//Constructor / Destructor
Configuration::Configuration(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Configuration::~Configuration(){}

//Configuration function
void Configuration::make_sensor_configuration(k4n::structure::Sensor* sensor){
  //---------------------------

  k4a_device_configuration_t configuration = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;

  //Field stuff
  configuration.color_format = k4n_struct->config.color.format;
  configuration.color_resolution = k4n_struct->config.color.resolution;
  configuration.depth_mode = k4n_struct->config.depth.mode;

  //Synchro stuff
  configuration.camera_fps = k4n_struct->fps.mode;
  configuration.depth_delay_off_color_usec = k4n_struct->config.synchro.depth_delay_off_color_us;
  configuration.wired_sync_mode = k4n_struct->config.synchro.wired_mode;
  configuration.subordinate_delay_off_master_usec = k4n_struct->config.synchro.subordinate_delay_off_master_us;
  configuration.disable_streaming_indicator = k4n_struct->config.synchro.disable_streaming_indicator;
  configuration.synchronized_images_only = k4n_struct->config.synchro.synchronized_images_only;

  //---------------------------
  sensor->device.configuration = configuration;
}
void Configuration::make_sensor_color_configuration(k4n::structure::Sensor* sensor){
  k4a::device& device = sensor->device.handle;
  //---------------------------

  device.set_color_control(k4n_struct->config.color.exposure.command, k4n_struct->config.color.exposure.mode, k4n_struct->config.color.exposure.value);
  device.set_color_control(k4n_struct->config.color.white_balance.command, k4n_struct->config.color.white_balance.mode, k4n_struct->config.color.white_balance.value);
  device.set_color_control(k4n_struct->config.color.brightness.command, k4n_struct->config.color.brightness.mode, k4n_struct->config.color.brightness.value);
  device.set_color_control(k4n_struct->config.color.contrast.command, k4n_struct->config.color.contrast.mode, k4n_struct->config.color.contrast.value);
  device.set_color_control(k4n_struct->config.color.saturation.command, k4n_struct->config.color.saturation.mode, k4n_struct->config.color.saturation.value);
  device.set_color_control(k4n_struct->config.color.sharpness.command, k4n_struct->config.color.sharpness.mode, k4n_struct->config.color.sharpness.value);
  device.set_color_control(k4n_struct->config.color.gain.command, k4n_struct->config.color.gain.mode, k4n_struct->config.color.gain.value);
  device.set_color_control(k4n_struct->config.color.backlight_compensation.command, k4n_struct->config.color.backlight_compensation.mode, k4n_struct->config.color.backlight_compensation.value);
  device.set_color_control(k4n_struct->config.color.power_frequency.command, k4n_struct->config.color.power_frequency.mode, k4n_struct->config.color.power_frequency.value);

  sensor->color.config = k4n_struct->config.color;
  sensor->depth.config = k4n_struct->config.depth;
  sensor->ir.config = k4n_struct->config.ir;

  //---------------------------
}
void Configuration::make_default_configuration(){
  //---------------------------

  k4n_struct->config.depth.mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
  k4n_struct->config.color.format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  k4n_struct->config.color.resolution = K4A_COLOR_RESOLUTION_1080P;

  k4n_struct->fps.mode = K4A_FRAMES_PER_SECOND_30;
  k4n_struct->config.synchro.depth_delay_off_color_us = 0;
  k4n_struct->config.synchro.wired_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
  k4n_struct->config.synchro.subordinate_delay_off_master_us = 0;
  k4n_struct->config.synchro.disable_streaming_indicator = true;
  k4n_struct->config.synchro.synchronized_images_only = true;

  k4n_struct->config.color.exposure.value = 15625;
  k4n_struct->config.color.white_balance.value = 4500;
  k4n_struct->config.color.brightness.value = 128;
  k4n_struct->config.color.contrast.value = 5;
  k4n_struct->config.color.saturation.value = 32;
  k4n_struct->config.color.sharpness.value = 2;
  k4n_struct->config.color.gain.value = 0;
  k4n_struct->config.color.backlight_compensation.value = 0;
  k4n_struct->config.color.power_frequency.value = 2;

  //---------------------------
}
void Configuration::find_playback_configuration(k4n::playback::Sensor* sensor){
  k4a_record_configuration_t configuration = sensor->playback.get_record_configuration();
  //---------------------------

  //FPS
  sensor->fps.mode_str = find_mode_fps(configuration.camera_fps);

  //Synchro
  k4n_struct->config.synchro.wired_mode_str = find_mode_synchro(configuration.wired_sync_mode);
  k4n_struct->config.synchro.wired_mode = configuration.wired_sync_mode;
  k4n_struct->config.synchro.depth_delay_off_color_us = configuration.depth_delay_off_color_usec;
  k4n_struct->config.synchro.subordinate_delay_off_master_us = configuration.subordinate_delay_off_master_usec;
  k4n_struct->config.synchro.start_timestamp_offset_us = configuration.start_timestamp_offset_usec;

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
  sensor->playback.get_tag("K4A_DEVICE_SERIAL_NUMBER", &sensor->serial_number);

  //---------------------------
}
void Configuration::reset_color_configuration(k4n::structure::Sensor* sensor){
  k4n::color::Structure* color = &sensor->color;
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
void Configuration::make_transformation_from_calibration(k4n::structure::Sensor* sensor){
  //---------------------------

  sensor->device.transformation = k4a::transformation(sensor->device.calibration);

  //---------------------------
}
void Configuration::make_capture_calibration(k4n::structure::Sensor* sensor){
  k4a::device& device = sensor->device.handle;
  //---------------------------

  sensor->device.calibration = device.get_calibration(k4n_struct->config.depth.mode, k4n_struct->config.color.resolution);

  //---------------------------
}
void Configuration::find_playback_calibration(k4n::playback::Sensor* sensor){
  //---------------------------

  sensor->device.calibration = sensor->playback.get_calibration();

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
