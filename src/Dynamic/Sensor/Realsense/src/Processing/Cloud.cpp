#include "Cloud.h"

#include <Realsense/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace rlx::processing{

//Constructor / Destructor
Cloud::Cloud(rlx::Node* node_realsense){
  //---------------------------

  this->rlx_struct = node_realsense->get_rlx_struct();

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::extract_data(dat::base::Sensor& sensor){
  rlx::base::Sensor* rlx_sensor = dynamic_cast<rlx::base::Sensor*>(&sensor);
  //---------------------------



  //---------------------------
}

}
