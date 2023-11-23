#include "K4A_playback.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>


//Constructor / Destructor
K4A_playback::K4A_playback(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;

  //---------------------------
}
K4A_playback::~K4A_playback(){}

//Main function
void K4A_playback::record_control(string path){
  //---------------------------

  k4a::playback recording = k4a::playback::open(path.c_str());
  k4a_record_configuration_t record_configuration = recording.get_record_configuration();
  struct_record.path = path;

  //FPS
  std::stringstream fpsSS;
  fpsSS << record_configuration.camera_fps;
  struct_record.info_fps = fpsSS.str();
  say(struct_record.info_fps);

  std::chrono::microseconds TimePerFrame;
  switch(record_configuration.camera_fps){
    case K4A_FRAMES_PER_SECOND_5:{
      TimePerFrame = std::chrono::microseconds(std::micro::den / (std::micro::num * 5));
      break;
    }
    case K4A_FRAMES_PER_SECOND_15:{
      TimePerFrame = std::chrono::microseconds(std::micro::den / (std::micro::num * 15));
      break;
    }
    case K4A_FRAMES_PER_SECOND_30:{
      TimePerFrame = std::chrono::microseconds(std::micro::den / (std::micro::num * 30));
      break;
    }
  }

  //Depth mode
  struct_record.is_depth = record_configuration.depth_track_enabled;
  struct_record.is_infrared = record_configuration.ir_track_enabled;
  struct_record.is_imu = record_configuration.imu_track_enabled;
  std::stringstream depthSS;
  if (struct_record.is_depth || struct_record.is_infrared){
    depthSS << record_configuration.depth_mode;
  }
  else{
    depthSS << "(None)";
  }
  struct_record.info_depth_mode = depthSS.str();

  //Color stuff
  struct_record.is_color = record_configuration.color_track_enabled;
  std::stringstream colorResolutionSS;
  std::stringstream colorFormatSS;
  if(struct_record.is_color){
    colorFormatSS << record_configuration.color_format;
    colorResolutionSS << record_configuration.color_resolution;

    recording.set_color_conversion(K4A_IMAGE_FORMAT_COLOR_BGRA32);
    record_configuration.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  }
  else{
    colorFormatSS << "(None)";
    colorResolutionSS << "(None)";
  }
  struct_record.info_color_format = colorFormatSS.str();
  struct_record.info_color_resolution = colorResolutionSS.str();

  // Sync info
  std::stringstream syncModeSS;
  syncModeSS << record_configuration.wired_sync_mode;
  struct_record.info_wired_sync_mode = syncModeSS.str();
  struct_record.info_depth_delay_off_color_us = record_configuration.depth_delay_off_color_usec;
  struct_record.info_subordinate_delay_off_master = record_configuration.subordinate_delay_off_master_usec;
  struct_record.info_start_timestamp_offset_us = record_configuration.start_timestamp_offset_usec;
  struct_record.info_recording_lenght_us = static_cast<uint64_t>(recording.get_recording_length().count());

  // Device info
  std::string info_device_serial_number;
  recording.get_tag("K4A_DEVICE_SERIAL_NUMBER", &info_device_serial_number);
  std::string info_color_firmware_version;
  recording.get_tag("K4A_COLOR_FIRMWARE_VERSION", &info_color_firmware_version);
  std::string info_depth_firmware_version;
  recording.get_tag("K4A_DEPTH_FIRMWARE_VERSION", &info_depth_firmware_version);
  struct_record.info_device_serial_number = info_device_serial_number;
  struct_record.info_color_firmware_version = info_color_firmware_version;
  struct_record.info_depth_firmware_version = info_depth_firmware_version;

  //---------------------------
}
