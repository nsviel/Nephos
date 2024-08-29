#include "Node.h"

#include <Core/Namespace.h>
#include <System/Namespace.h>


namespace sys{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  //Dependancy
  this->node_vulkan = node_core->get_node_vulkan();

  //Child
  this->node_profiler = new prf::Node(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_profiler->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_profiler->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_profiler->gui();

  //---------------------------
}


}
