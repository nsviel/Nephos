#include "K4A_recording.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>


//Constructor / Destructor
K4A_recording::K4A_recording(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;

  //---------------------------
}
K4A_recording::~K4A_recording(){}

//Main function
void K4A_recording::record_control(string path){
  //---------------------------

  k4a::playback recording = k4a::playback::open(path.c_str());
  k4a_record_configuration_t record_configuration = recording.get_record_configuration();

  //FPS
  std::stringstream fpsSS;
  fpsSS << record_configuration.camera_fps;
  string info_fps = fpsSS.str();

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
  bool is_depth = record_configuration.depth_track_enabled;
  bool is_infrared = record_configuration.ir_track_enabled;
  std::stringstream depthSS;
  if (is_depth || is_infrared)
  {
      depthSS << record_configuration.depth_mode;
  }
  else
  {
      depthSS << "(None)";
  }
  string info_depth_mode = depthSS.str();

  //Color stuff
  bool is_color = record_configuration.color_track_enabled;
  std::stringstream colorResolutionSS;
  std::stringstream colorFormatSS;
  if(is_color){
    colorFormatSS << record_configuration.color_format;
    colorResolutionSS << record_configuration.color_resolution;

    recording.set_color_conversion(K4A_IMAGE_FORMAT_COLOR_BGRA32);
    record_configuration.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  }
  else{
    colorFormatSS << "(None)";
    colorResolutionSS << "(None)";
  }
  string info_color_format = colorFormatSS.str();
  string info_color_resolution = colorResolutionSS.str();

  // Sync info
  int32_t m_depthDelayOffColorUsec = record_configuration.depth_delay_off_color_usec;
  std::stringstream syncModeSS;
  syncModeSS << record_configuration.wired_sync_mode;
  string m_wiredSyncModeLabel = syncModeSS.str();

  uint32_t m_subordinateDelayOffMasterUsec = record_configuration.subordinate_delay_off_master_usec;
  uint32_t m_startTimestampOffsetUsec = record_configuration.start_timestamp_offset_usec;
  uint64_t m_recordingLengthUsec = static_cast<uint64_t>(recording.get_recording_length().count());

  // Device info
  std::string m_deviceSerialNumber;
  recording.get_tag("K4A_DEVICE_SERIAL_NUMBER", &m_deviceSerialNumber);
  std::string m_colorFirmwareVersion;
  recording.get_tag("K4A_COLOR_FIRMWARE_VERSION", &m_colorFirmwareVersion);
  std::string m_depthFirmwareVersion;
  recording.get_tag("K4A_DEPTH_FIRMWARE_VERSION", &m_depthFirmwareVersion);

  say(m_deviceSerialNumber);

  //---------------------------
}
