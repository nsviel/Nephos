#include "Node.h"

#include <Radiometry/Calibration/Namespace.h>


namespace rad::cal{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  this->node_vulkan = node_module->get_node_vulkan();
  this->node_core = node_module->get_node_core();
  this->node_data = node_core->get_node_data();
  this->node_profiler = node_core->get_node_profiler();

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
