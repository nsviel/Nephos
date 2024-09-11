#include "Capture.h"

#include <Realsense/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace rlx::capture{

//Constructor / Destructor
Capture::Capture(rlx::Node* node_realsense){
  //---------------------------

  dat::Node* node_data = node_realsense->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->dat_sensor = node_element->get_dat_sensor();
  this->rlx_struct = node_realsense->get_rlx_struct();
  this->rlx_configuration = new rlx::capture::Configuration(node_realsense);

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::init(rlx::capture::Sensor& sensor){
  //---------------------------

  rlx_configuration->init(sensor);
  this->init_info(sensor);
  this->init_capture(sensor);
  dat_sensor->init_sensor(sensor);

  //---------------------------
}
void Capture::capture(dat::base::Sensor& sensor){
  rlx::capture::Sensor* rlx_sensor = dynamic_cast<rlx::capture::Sensor*>(&sensor);
  //---------------------------

  prf::monitor::Tasker* tasker = sensor.profiler.fetch_tasker("capture");
  tasker->loop();

  // Wait for the next set of frames from the camera
  tasker->task_begin("data");
  rlx_sensor->device.frame_set = rlx_sensor->device.pipe.wait_for_frames();
  tasker->task_end("data");

  //Make alignment
  tasker->task_begin("alignment");
  rlx_sensor->device.frame_set = rlx_sensor->device.aligner.process(rlx_sensor->device.frame_set);
  tasker->task_end("alignment");

  //---------------------------
}
void Capture::clean(rlx::capture::Sensor& sensor){
  //---------------------------

  dat_sensor->clean_sensor(sensor);
  sensor.device.pipe.stop();

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
    sensor.device.pipe.start(sensor.device.configuration);
  }

  //---------------------------
}

}
