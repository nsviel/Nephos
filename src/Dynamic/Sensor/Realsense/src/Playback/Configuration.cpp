#include "Configuration.h"

#include <Realsense/Namespace.h>
#include <Utility/Namespace.h>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace rlx::playback{

//Constructor / Destructor
Configuration::Configuration(rlx::Node* node_realsense){
  //---------------------------

  this->rlx_struct = node_realsense->get_rlx_struct();

  //---------------------------
}
Configuration::~Configuration(){}

//Main function
void Configuration::init(rlx::capture::Sensor& sensor){
  //---------------------------

  sensor.device.configuration.enable_stream(RS2_STREAM_COLOR, RS2_FORMAT_BGR8); // Color stream
  sensor.device.configuration.enable_stream(RS2_STREAM_DEPTH, RS2_FORMAT_Z16);  // Depth stream
  sensor.device.configuration.enable_stream(RS2_STREAM_INFRARED);  // Infrared stream

  //---------------------------
}

}
