#include "Transformation.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::data{

//Constructor / Destructor
Transformation::Transformation(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_depth = new k4n::depth::Data(node_k4n);
  this->k4n_ir = new k4n::image::Infrared(node_k4n);
  this->k4n_depth_to_color = new k4n::transformation::Depth_to_color(node_k4n);
  this->k4n_color_to_depth = new k4n::transformation::Color_to_depth(node_k4n);
  this->k4n_table = new k4n::processing::Table_xy(node_k4n);

  //---------------------------
}
Transformation::~Transformation(){}

//Main function
void Transformation::make_transformation(dat::base::Sensor& sensor){
  k4n::base::Sensor* k4n_sensor = dynamic_cast<k4n::base::Sensor*>(&sensor);
  //---------------------------

  switch(k4n_struct->transformation.mode){
    case k4n::transformation::DEPTH_TO_COLOR:{
      k4n_depth_to_color->make_transformation(*k4n_sensor);
      break;
    }
    case k4n::transformation::COLOR_TO_DEPTH:{
      k4n_color_to_depth->make_transformation(*k4n_sensor);
      break;
    }
  }

  //---------------------------
}

}
