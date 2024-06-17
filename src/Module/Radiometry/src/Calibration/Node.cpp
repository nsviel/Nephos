#include "Node.h"

#include <Radiometry/Namespace.h>


namespace rad::calibration{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  this->node_radio = node_radio;
  this->rad_struct = new rad::calibration::Structure();

  //---------------------------
}
Node::~Node(){}

//Main function



}
