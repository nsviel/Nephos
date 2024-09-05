#include "Detach.h"

#include <USB/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace usb{

//Constructor / Destructor
Detach::Detach(usb::Node* node_usb){
  //---------------------------

  this->usb_struct = node_usb->get_usb_struct();

  //---------------------------
}
Detach::~Detach(){}

//Main function
void Detach::manage_action() {
  //---------------------------

  std::string node = std::string(udev_device_get_devnode(usb_struct->udev.device));
  auto it = usb_struct->map_device.find(node);
  if (it != usb_struct->map_device.end()) {
    say(usb_struct->map_device[node]);
    say("unplug");
  }

  //---------------------------
}

}
