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
void K4A_recorder::record_mkv(Struct_k4a_device* device){
  //---------------------------

/*
  const char* recordingPath = "output.mkv";

  // Create a k4a::record instance
  k4a::record recording = k4a::record::create(recordingPath, *device->device, device->config.k4a_config);

  // Add tags and additional configurations if needed
  recording.add_tag("Tag1", "Value1");
  // Add more tags or configurations as needed

  // Start recording
  recording.write_header();

  // Capture loop
  const int numFramesToRecord = 150; // Record for 10 seconds at 30 FPS
  for (int i = 0; i < numFramesToRecord; ++i)
  {
      // Acquire a capture from the device
      k4a::capture capture;
      if (device->device->get_capture(&capture, std::chrono::milliseconds(1000)))
      {
          // Write the capture to the recording
          recording.write_capture(capture);
      }
  }

  // Stop recording and close the file
  recording.flush();
*/
  //---------------------------
}
