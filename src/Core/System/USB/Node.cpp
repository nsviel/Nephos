#include "Node.h"

#include <System/Namespace.h>


namespace usb{

//Constructor / Destructor
Node::Node(sys::Node* node_system){
  //---------------------------

  this->node_io = node_system->get_node_io();

  this->usb_struct = new usb::Structure();
  this->usb_monitor = new usb::Monitor(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  usb_monitor->init();

  //---------------------------
}

}
