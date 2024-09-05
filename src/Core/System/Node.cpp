#include "Node.h"

#include <Core/Namespace.h>
#include <System/Namespace.h>
#include <Profiler/Namespace.h>


namespace sys{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  //Dependancy
  this->node_io = node_core->get_node_io();
  this->node_vulkan = node_core->get_node_vulkan();

  //Child
  this->node_usb = new usb::Node(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_usb->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------


  //---------------------------
}
void Node::gui(){
  //---------------------------

  //---------------------------
}


}
