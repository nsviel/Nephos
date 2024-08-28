#include "Sensor.h"

#include <Kinect/Namespace.h>


namespace k4n::base{

//Constructor / Destructor
Sensor::Sensor(){
  //---------------------------

  this->info.model = "kinect";
  this->data.topology.type = utl::topology::POINT;
  this->data.nb_data_max = 10000000;
  this->info.depth_mode = "NFOV";
  this->info.vec_depth_mode.push_back("NFOV");
  this->info.vec_depth_mode.push_back("WFOV");
  this->calibration.path.insert("../media/calibration/kinect.json");

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::clean(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

}
