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
  tasker->task_begin("transformation");
  k4n_transformation->make_transformation(*k4n_sensor);
  tasker->task_end("transformation");

  //Extraction
  tasker->task_begin("extraction");
  k4n_color->extract_data(*k4n_sensor);
  k4n_intensity->extract_data(*k4n_sensor);
  k4n_location->extract_data(*k4n_sensor);
  tasker->task_end("extraction");

  //---------------------------
}

//Subfunction
bool Cloud::check_condition(k4n::base::Sensor& sensor){
  //---------------------------

  if(!sensor.color.data.image.is_valid()) return false;
  if(!sensor.depth.data.image.is_valid()) return false;
  if(!sensor.infra.data.image.is_valid()) return false;

  //---------------------------
  return true;
}

}
