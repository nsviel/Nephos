#include "Data.h"

#include <Kinect/Namespace.h>
#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_transformation = new k4n::processing::image::Transformation(node_k4n);
  this->k4n_color = new k4n::processing::image::Color(node_k4n);
  this->k4n_depth = new k4n::processing::image::Depth(node_k4n);
  this->k4n_ir = new k4n::processing::image::Infrared(node_k4n);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::extract_data(k4n::structure::Sensor* sensor){
  //---------------------------

  this->extract_image_data(sensor);
  this->make_transformation(sensor);

  //---------------------------
}

//Subfunction
void Data::extract_image_data(k4n::structure::Sensor* sensor){
  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("kinect::image");
  //---------------------------

  tasker->loop();

  //Depth data
  tasker->task_begin("depth");
  k4n_depth->extract_data(sensor);
  tasker->task_end("depth");

  //Color data
  tasker->task_begin("color");
  k4n_color->extract_data(sensor);
  tasker->task_end("color");

  //Infrared data
  tasker->task_begin("infrared");
  k4n_ir->extract_data(sensor);
  tasker->task_end("infrared");

  //---------------------------
}
void Data::make_transformation(k4n::structure::Sensor* sensor){
  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("kinect::image");
  //---------------------------

  tasker->task_begin("transformation");
  k4n_transformation->make_transformation(sensor);
  tasker->task_end("transformation");

  //---------------------------
}

}
