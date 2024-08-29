#include "Node.h"

#include <Radiometry/Namespace.h>
#include <Radiometry/Calibration/Namespace.h>
#include <Core/Namespace.h>
#include <System/Namespace.h>


namespace rad::cal{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  core::Node* node_core = node_radio->get_node_core();
  sys::Node* node_system = node_core->get_node_system();

  this->node_core = node_core;
  this->node_data = node_core->get_node_data();
  this->node_profiler = node_system->get_node_profiler();

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
