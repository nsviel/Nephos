#include "Attach.h"

#include <USB/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace usb{

//Constructor / Destructor
Attach::Attach(usb::Node* node_usb){
  //---------------------------

  this->usb_struct = node_usb->get_usb_struct();

  //---------------------------
}
Attach::~Attach(){}

//Main function
void Attach::manage_action() {
  //---------------------------

  std::string serial = std::string(udev_device_get_sysattr_value(usb_struct->udev.device, "serial"));
  std::string vendor = std::string(udev_device_get_sysattr_value(usb_struct->udev.device, "idVendor"));
  std::string product = std::string(udev_device_get_sysattr_value(usb_struct->udev.device, "idProduct"));
  std::string node = std::string(udev_device_get_devnode(usb_struct->udev.device));
/*
  for(int i=0; i<usb_struct->vec_reference.size(); i++){
    usb::structure::Reference& ref = usb_struct->vec_reference[i];

    if (vendor == ref.vendor && product == ref.product) {
      say(serial);
      say("plug");

      usb_struct->map_device[node] = serial;
    }
  }
*/
  //---------------------------
}

}
