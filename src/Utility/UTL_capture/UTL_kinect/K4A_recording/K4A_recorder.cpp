#include "K4A_recorder.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>


//Constructor / Destructor
K4A_recorder::K4A_recorder(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;

  //---------------------------
}
K4A_recorder::~K4A_recorder(){}

//Main function
void K4A_recorder::record_mkv(string path){
  //---------------------------

  const char* recordingPath = "output.mkv";

  // Configure the device
  k4a_device_configuration_t deviceConfig = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
  deviceConfig.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  deviceConfig.color_resolution = K4A_COLOR_RESOLUTION_1080P;
  deviceConfig.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
  deviceConfig.camera_fps = K4A_FRAMES_PER_SECOND_30;

  // Open the device
  k4a::device device = k4a::device::open(0);

  // Create a k4a::record instance
  k4a::record recording = k4a::record::create(recordingPath, device, deviceConfig);

  // Add tags and additional configurations if needed
  recording.add_tag("Tag1", "Value1");
  // Add more tags or configurations as needed

  // Start recording
  recording.write_header();

  // Capture loop
  const int numFramesToRecord = 300; // Record for 10 seconds at 30 FPS
  for (int i = 0; i < numFramesToRecord; ++i)
  {
      // Acquire a capture from the device
      k4a::capture capture;
      if (device.get_capture(&capture, std::chrono::milliseconds(1000)))
      {
          // Write the capture to the recording
          recording.write_capture(capture);
      }
  }

  // Stop recording and close the file
  recording.flush();

  //---------------------------
}
