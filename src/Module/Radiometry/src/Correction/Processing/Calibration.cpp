#include "Calibration.h"

#include <Radiometry/Namespace.h>


namespace rad::correction{

//Constructor / Destructor
Calibration::Calibration(rad::Node* node_radio){
  //---------------------------

  rad::correction::Node* node_correction = node_radio->get_node_correction();

  this->rad_struct = node_correction->get_rad_struct();

  //---------------------------
}
Calibration::~Calibration(){}

//Main function



}
