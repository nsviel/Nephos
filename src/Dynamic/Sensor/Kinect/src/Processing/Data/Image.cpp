#include "Image.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::data{

//Constructor / Destructor
Image::Image(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_color = new k4n::image::Color(node_k4n);
  this->k4n_depth = new k4n::image::Depth(node_k4n);
  this->k4n_ir = new k4n::image::Infrared(node_k4n);
  this->k4n_depth_to_color = new k4n::transformation::Depth_to_color(node_k4n);
  this->k4n_color_to_depth = new k4n::transformation::Color_to_depth(node_k4n);
  this->k4n_table = new k4n::processing::Table_xy(node_k4n);

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::extract_data(dat::base::Sensor& sensor){
  k4n::base::Sensor* k4n_sensor = dynamic_cast<k4n::base::Sensor*>(&sensor);
  //---------------------------

  prf::monitor::Tasker* tasker = sensor.profiler.fetch_tasker("image");
  tasker->loop();

  //Depth data
  tasker->task_begin("depth");
  k4n_depth->extract_data(*k4n_sensor);
  tasker->task_end("depth");

  //Color data
  tasker->task_begin("color");
  k4n_color->extract_data(*k4n_sensor);
  tasker->task_end("color");

  //Infrared data
  tasker->task_begin("infrared");
  k4n_ir->extract_data(*k4n_sensor);
  tasker->task_end("infrared");

  tasker->task_begin("transformation");
  this->make_transformation(*k4n_sensor);
  tasker->task_end("transformation");

  k4n_table->build_table_xy(*k4n_sensor);

  //---------------------------
}

//Subfunction
void Image::make_transformation(k4n::base::Sensor& sensor){
  //---------------------------

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

  //---------------------------
}

}
