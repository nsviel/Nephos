#include "Data.h"

#include <Kinect/Namespace.h>
#include <Core/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Data::Data(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_color = new k4n::processing::image::Color(node_k4n);
  this->k4n_depth = new k4n::processing::image::Depth(node_k4n);
  this->k4n_ir = new k4n::processing::image::Infrared(node_k4n);
  this->k4n_depth_to_color = new k4n::processing::image::Depth_to_color(node_k4n);
  this->k4n_color_to_depth = new k4n::processing::image::Color_to_depth(node_k4n);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::extract_data(k4n::base::Sensor* sensor){
  //---------------------------

  this->extract_image_data(sensor);
  this->make_transformation(sensor);

  //---------------------------
}

//Subfunction
void Data::extract_image_data(k4n::base::Sensor* sensor){
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
void Data::make_transformation(k4n::base::Sensor* sensor){
  prf::dynamic::Tasker* tasker = sensor->profiler.fetch_tasker("kinect::image");
  //---------------------------

  tasker->task_begin("transformation");
  switch(k4n_struct->transformation.mode){
    case k4n::transformation::DEPTH_TO_COLOR:{
      k4n_depth_to_color->make_transformation(sensor);
      break;
    }
    case k4n::transformation::COLOR_TO_DEPTH:{
      k4n_color_to_depth->make_transformation(sensor);
      break;
    }
  }
  tasker->task_end("transformation");

  //---------------------------
}

}
