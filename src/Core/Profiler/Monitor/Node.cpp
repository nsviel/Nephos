#include "Node.h"

#include <Profiler/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace prf::monitor{

Node::Node(prf::Node* node_profiler){
  //---------------------------

  this->node_vulkan = node_profiler->get_node_vulkan();

  this->prf_struct = new prf::monitor::Structure();
  this->prf_manager = new prf::monitor::Manager(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  prf_manager->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  prf_manager->loop(120);

  //---------------------------
}


}
