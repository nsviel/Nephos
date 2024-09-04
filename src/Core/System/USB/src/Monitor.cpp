#include "Monitor.h"

#include <USB/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace usb{

//Constructor / Destructor
Monitor::Monitor(usb::Node* node_usb){
  //---------------------------

  this->usb_struct = node_usb->get_usb_struct();

  //---------------------------
}
Monitor::~Monitor(){}

//Main function
void Monitor::init() {
  //---------------------------

  //Contexte
  usb_struct->udev.contexte = udev_new();
  if (!usb_struct->udev.contexte) {
    std::cerr << "Can't create udev\n";
    return;
  }

  //USB listener
  usb_struct->udev.monitor = udev_monitor_new_from_netlink(usb_struct->udev.contexte, "udev");

  //Add filter
  udev_monitor_filter_add_match_subsystem_devtype(usb_struct->udev.monitor, "usb", "usb_device");

  //Enable monitor to receive events
  udev_monitor_enable_receiving(usb_struct->udev.monitor);

  //Get file descriptor
  usb_struct->udev.fd = udev_monitor_get_fd(usb_struct->udev.monitor);


  // Create and run the thread
  std::thread monitor_thread(&Monitor::loop, this);
  monitor_thread.detach();

  //---------------------------
}
void Monitor::loop() {
  //---------------------------

  while (true) {
    //Prepare file descriptor
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(usb_struct->udev.fd, &fds);

    // Wait for an event on the file descriptor
    int ret = select(usb_struct->udev.fd + 1, &fds, NULL, NULL, NULL);
    int event = FD_ISSET(usb_struct->udev.fd, &fds);

    //Even occur
    if (ret > 0 && event) {
      this->manage_event();
    }
  }

  //---------------------------
}
void Monitor::close() {
  //---------------------------

  udev_monitor_unref(usb_struct->udev.monitor);
  udev_unref(usb_struct->udev.contexte);

  //---------------------------
}

//Subfunction
void Monitor::manage_event() {
  //---------------------------

  //Event associated device
  usb_struct->udev.device = udev_monitor_receive_device(usb_struct->udev.monitor);
  if (!usb_struct->udev.device) return;

  std::string action = std::string(udev_device_get_action(usb_struct->udev.device));
  std::string serial = std::string(udev_device_get_sysattr_value(usb_struct->udev.device, "serial"));
  std::string vendor = std::string(udev_device_get_sysattr_value(usb_struct->udev.device, "idVendor"));
  std::string product = std::string(udev_device_get_sysattr_value(usb_struct->udev.device, "idProduct"));

  for(int i=0; i<usb_struct->vec_device.size(); i++){
    usb::structure::Device& device = usb_struct->vec_device[i];

    if (vendor == device.vendor && product == device.product) {
      this->manage_action(action, product);
    }
  }

  //Release device
  udev_device_unref(usb_struct->udev.device);

  //---------------------------
}
void Monitor::manage_action(const std::string& action, const std::string& product) {
  //---------------------------

  //Plugging
  if(action == "add"){
    say("is plugging");
  }
  //Unplugging
  else if(action == "add"){
    say("is unplugging");
  }

  //---------------------------
}

}
