#include "Cloud.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::data{

//Constructor / Destructor
Cloud::Cloud(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_color = new k4n::cloud::Color(node_k4n);
  this->k4n_intensity = new k4n::cloud::Intensity(node_k4n);
  this->k4n_location = new k4n::cloud::Location(node_k4n);
  this->k4n_transformation = new k4n::transformation::Depth_to_cloud(node_k4n);
  this->atr_field = new dat::atr::Field();
  this->atr_location = new dat::atr::Location();

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::extract_data(dat::base::Sensor& sensor){
  k4n::base::Sensor* k4n_sensor = dynamic_cast<k4n::base::Sensor*>(&sensor);
  if(check_condition(*k4n_sensor) == false) return;
  //---------------------------

  prf::monitor::Tasker* tasker = k4n_sensor->profiler.fetch_tasker("cloud");
  tasker->loop();

  //init
  tasker->task_begin("init");
  k4n_transformation->make_transformation(*k4n_sensor);
  tasker->task_end("init");

  //Extraction
  tasker->task_begin("extraction");
  k4n_color->extract_data(*k4n_sensor);
  k4n_intensity->extract_data(*k4n_sensor);
  k4n_location->extract_data(*k4n_sensor);
  tasker->task_end("extraction");

  //Transfer
  tasker->task_begin("transfer");
  this->extraction_transfer(*k4n_sensor);
  tasker->task_end("transfer");

  atr_location->compute_height(*k4n_sensor);

  //---------------------------
}

//Subfunction
bool Cloud::check_condition(k4n::base::Sensor& sensor){
  //---------------------------

  if(!sensor.depth.data.image.is_valid()) return false;
  if(!sensor.infra.data.image.is_valid()) return false;
  if(sensor.color.data.buffer == nullptr) return false;
  if(sensor.color.data.size != sensor.depth.data.size * 2) return false;

  //---------------------------
  return true;
}
void Cloud::extraction_transfer(k4n::base::Sensor& sensor){
  utl::base::Data& data = *sensor.data;
  //---------------------------

  std::unique_lock<std::mutex> lock(data.mutex);

  //Info
  data.size = sensor.depth.cloud.size;
  data.width = sensor.depth.cloud.width;
  data.height = sensor.depth.cloud.height;

  //---------------------------
}

}
