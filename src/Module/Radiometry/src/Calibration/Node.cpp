#include "Node.h"

#include <Radiometry/Namespace.h>


namespace rad::calibration{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  rad::correction::Node* node_correction = node_radio->get_node_correction();

  this->rad_struct = node_correction->get_rad_struct();

  //---------------------------
}
Node::~Node(){}

//Main function



}
