#include "Correction.h"

#include <Radiometry/Namespace.h>


namespace rad{

//Constructor / Destructor
Correction::Correction(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();

  //---------------------------
}
Correction::~Correction(){}

//Main function


}
