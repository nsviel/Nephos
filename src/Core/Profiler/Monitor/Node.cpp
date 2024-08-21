#include "Node.h"

#include <Profiler/Namespace.h>
#include <Core/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace prf{

Node::Node(prf::Node* node_profiler){
  //---------------------------

  this->node_vulkan = node_core->get_node_vulkan();

  this->prf_struct = new prf::monitor::Structure();
  this->prf_monitor = new prf::monitor::Manager(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  prf_monitor->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  prf_monitor->loop(120);

  //---------------------------
}


}
