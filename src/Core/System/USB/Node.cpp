#include "Node.h"

#include <System/Namespace.h>


namespace usb{

//Constructor / Destructor
Node::Node(sys::Node* node_system){
  //---------------------------

  this->usb_struct = new usb::Structure();
  this->usb_monitor = new usb::Monitor(this);
  this->usb_device = new usb::Device(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  usb_device->init();
  usb_monitor->init();

  //---------------------------
}

}
