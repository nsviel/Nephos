#include "Node.h"

#include <Profiler/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace prf::hardware{

Node::Node(prf::Node* node_profiler){
  //---------------------------

  this->node_vulkan = node_profiler->get_node_vulkan();

  this->prf_struct = new prf::hardware::Structure();
  this->prf_manager = new prf::hardware::Manager(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  prf_manager->init();

  //---------------------------
}

}
