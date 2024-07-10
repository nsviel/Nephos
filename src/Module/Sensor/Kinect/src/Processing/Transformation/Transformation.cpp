#include "Transformation.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::processing::image{

//Constructor / Destructor
Transformation::Transformation(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_depth_to_color = new k4n::processing::image::Depth_to_color();
  this->k4n_color_to_depth = new k4n::processing::image::Color_to_depth();

  //---------------------------
}
Transformation::~Transformation(){}

//Main function
void Transformation::make_transformation(k4n::base::Sensor* sensor){
  //---------------------------

  switch(k4n_struct->config.depth.transformation_mode){
    case k4n::depth::DEPTH_TO_COLOR:{
      k4n_depth_to_color->make_transformation(sensor);
      break;
    }
    case k4n::depth::COLOR_TO_DEPTH:{
      k4n_color_to_depth->make_transformation(sensor);
      break;
    }
  }

  //---------------------------
}

}
