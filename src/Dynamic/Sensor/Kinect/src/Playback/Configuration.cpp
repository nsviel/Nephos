#include "Configuration.h"

#include <Kinect/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Configuration::Configuration(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Configuration::~Configuration(){}

//Main function
void Configuration::init_configuration(k4n::playback::Sensor& sensor){
  //---------------------------

  this->find_configuration(sensor);
  this->find_calibration(sensor);

  //---------------------------
}
void Configuration::find_configuration(k4n::playback::Sensor& sensor){
  k4a_record_configuration_t configuration = sensor.device.playback.get_record_configuration();
  //---------------------------

  //FPS
  sensor.setting.fps_mode = find_mode_fps(configuration.camera_fps);

  //Synchro
  sensor.setting.wired_mode = find_mode_synchro(configuration.wired_sync_mode);
  k4n_struct->config.synchro.wired_mode = configuration.wired_sync_mode;
  k4n_struct->config.synchro.depth_delay_off_color_us = configuration.depth_delay_off_color_usec;
  k4n_struct->config.synchro.subordinate_delay_off_master_us = configuration.subordinate_delay_off_master_usec;
  k4n_struct->config.synchro.start_timestamp_offset_us = configuration.start_timestamp_offset_usec;

  //Depth
  sensor.info.depth_mode = find_mode_depth(configuration.depth_mode);
  sensor.setting.depth_resolution = find_resolution_depth(configuration.depth_mode);
  sensor.depth.config.enabled = configuration.depth_track_enabled;
  sensor.depth.config.mode = configuration.depth_mode;
  sensor.device.playback.get_tag("K4A_DEPTH_FIRMWARE_VERSION", &sensor.firmware.depth);

  //Color
  k4a_image_format_t required_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  sensor.device.playback.set_color_conversion(required_format);
  configuration.color_format = required_format;

  sensor.setting.color_resolution = find_mode_color_resolution(configuration.color_resolution);
  sensor.setting.color_format = find_mode_color_format(configuration.color_format);
  sensor.color.config.enabled = configuration.color_track_enabled;
  sensor.color.config.resolution = configuration.color_resolution;
  sensor.color.config.format = configuration.color_format;
  sensor.device.playback.get_tag("K4A_COLOR_FIRMWARE_VERSION", &sensor.firmware.color);

  //Device
  sensor.infra.config.enabled = configuration.ir_track_enabled;
  sensor.imu.config.enabled = configuration.imu_track_enabled;
  sensor.device.playback.get_tag("K4A_DEVICE_SERIAL_NUMBER", &sensor.info.serial_number);

  //---------------------------
}
void Configuration::find_calibration(k4n::playback::Sensor& sensor){
  //---------------------------

  sensor.device.calibration = sensor.device.playback.get_calibration();
  sensor.device.transformation = k4a::transformation(sensor.device.calibration);

  //---------------------------
}

//Subfunction
std::string Configuration::find_mode_fps(int mode){
  std::string mode_str = "";
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
std::string Configuration::find_mode_synchro(int mode){
  std::string mode_str = "";
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
std::string Configuration::find_mode_depth(int mode){
  std::string mode_str = "";
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
std::string Configuration::find_resolution_depth(int mode){
  std::string mode_str = "";
  //---------------------------

  switch(mode){
    case K4A_DEPTH_MODE_OFF:{
      mode_str = "";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_2X2BINNED:{
      mode_str = "320x288";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_UNBINNED:{
      mode_str = "640x576";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_2X2BINNED:{
      mode_str = "512x512";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_UNBINNED:{
      mode_str = "1024x1024";
      break;
    }
    case K4A_DEPTH_MODE_PASSIVE_IR:{
      mode_str = "1024x1024";
      break;
    }
  }

  //---------------------------
  return mode_str;
}
std::string Configuration::find_mode_color_resolution(int mode){
  std::string mode_str = "";
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
std::string Configuration::find_mode_color_format(int mode){
  std::string mode_str = "";
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
float Configuration::find_mkv_ts_beg(std::string path){
  //---------------------------

  k4a::playback playback = k4a::playback::open(path.c_str());;
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_BEGIN);

  k4a::capture capture;
  k4a::image color = nullptr;
  while(color == nullptr){
    playback.get_next_capture(&capture);
    color = capture.get_color_image();
  }

  float ts_beg = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
  return ts_beg;
}
float Configuration::find_mkv_ts_end(std::string path){
  //---------------------------

  k4a::playback playback = k4a::playback::open(path.c_str());;
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_END);

  k4a::capture capture;
  k4a::image color = nullptr;
  while(color == nullptr){
    playback.get_previous_capture(&capture);
    color = capture.get_color_image();
  }

  float ts_end = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
  return ts_end;
}

}
