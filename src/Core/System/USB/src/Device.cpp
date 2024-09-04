#include "Device.h"

#include <USB/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace usb{

//Constructor / Destructor
Device::Device(usb::Node* node_usb){
  //---------------------------

  this->usb_struct = node_usb->get_usb_struct();

  //---------------------------
}
Device::~Device(){}

//Main function
void Device::init() {
  //---------------------------



  //---------------------------
}

}
