#include "Capture.h"

#include <Realsense/Namespace.h>
#include <Utility/Namespace.h>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace rlx::capture{

//Constructor / Destructor
Capture::Capture(rlx::Node* node_realsense){
  //---------------------------

  this->rlx_struct = node_realsense->get_rlx_struct();

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::init(rlx::capture::Sensor& sensor){
  //---------------------------

  this->init_info(sensor);
  this->init_capture(sensor);

  //---------------------------
}
void Capture::capture(dat::base::Sensor& sensor){
  rlx::capture::Sensor* rlx_sensor = dynamic_cast<rlx::capture::Sensor*>(&sensor);
  //---------------------------

  // Wait for the next set of frames from the camera
  rlx_sensor->frameset = rlx_struct->pipe.wait_for_frames();

  //---------------------------
}

//Subfunction
void Capture::init_info(rlx::capture::Sensor& sensor){
  //---------------------------

  sensor.type_sensor = "capture";
  sensor.device.index = rlx_struct->current_ID++;
  sensor.name = "capture_" + std::to_string(sensor.device.index);
  sensor.calibration.path.insert("../media/calibration/kinect.json");

  sensor.info.model = "realsense";
  sensor.data->name = sensor.name;
  sensor.data->topology.type = utl::topology::POINT;
  sensor.data->nb_data_max = 10000000;
  sensor.data->path.directory = utl::path::get_current_path_abs();
  sensor.pose->model[2][3] = 1;

  //---------------------------
}
void Capture::init_capture(rlx::capture::Sensor& sensor){
  //---------------------------

  rs2::device_list devices = rlx_struct->context.query_devices(); // Get number of connected devices
  int nb_device = devices.size();
  if(nb_device != 0){
    rlx_struct->pipe.start();
  }

  //---------------------------
}

}
