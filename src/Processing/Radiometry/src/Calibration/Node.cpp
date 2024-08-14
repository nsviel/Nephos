#include "Node.h"

#include <Radiometry/Namespace.h>


namespace rad::calibration{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  this->node_radio = node_radio;
  this->rad_struct = new rad::calibration::Structure();
  this->rad_process = new rad::calibration::Process(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::loop(){
  //---------------------------

  rad_process->loop();

  //---------------------------
}


}
