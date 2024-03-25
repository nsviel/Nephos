#include "Calibration.h"

#include <K4N/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->map_step[k4n::calibration::WAIT_VALIDATION] = "Wait validation";
  this->map_step[k4n::calibration::PROCESSING] = "Processing";
  this->step = k4n::calibration::WAIT_VALIDATION;

  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::validate_bbox(k4n::dev::Sensor* sensor){
  if(sensor->detection.nb_detection == 0) return;
  //---------------------------

  this->step++;

  //---------------------------
}


}
