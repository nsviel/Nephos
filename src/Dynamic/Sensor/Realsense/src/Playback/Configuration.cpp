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
void Configuration::init(rlx::playback::Sensor& sensor){
  //---------------------------

  sensor.device.configuration.enable_device_from_file(sensor.data->path.build());

  //---------------------------
}

}
