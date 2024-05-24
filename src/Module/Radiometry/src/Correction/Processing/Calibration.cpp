#include "Calibration.h"

#include <Radiometry/Namespace.h>


namespace rad::correction{

//Constructor / Destructor
Calibration::Calibration(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();

  //---------------------------
}
Calibration::~Calibration(){}

//Main function



}
