#include "Node.h"

#include <Radiometry/Calibration/Namespace.h>


namespace rad::cal{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  this->node_radio = node_radio;
  this->rad_struct = new rad::cal::Structure();
  this->rad_process = new rad::cal::Process(this);

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
