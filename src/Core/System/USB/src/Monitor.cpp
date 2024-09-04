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
  usb_struct->udev = udev_new();
  if (!usb_struct->udev) {
    std::cerr << "Can't create udev\n";
    return;
  }

  //USB listener
  usb_struct->monitor = udev_monitor_new_from_netlink(usb_struct->udev, "udev");

  //Add filter
  udev_monitor_filter_add_match_subsystem_devtype(usb_struct->monitor, "usb", "usb_device");

  //Enable monitor to receive events
  udev_monitor_enable_receiving(usb_struct->monitor);

  //Get file descriptor
  usb_struct->fd = udev_monitor_get_fd(usb_struct->monitor);


  // Create and run the thread
  std::thread monitor_thread(&Monitor::usb_monitor, this);
  monitor_thread.detach();

  //---------------------------
}
void Monitor::usb_monitor() {
  //---------------------------

  while (true) {
    //Prepare file descriptor
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(usb_struct->fd, &fds);

    // Wait for an event on the file descriptor
    int ret = select(usb_struct->fd + 1, &fds, NULL, NULL, NULL);
    int event = FD_ISSET(usb_struct->fd, &fds);

    //Even occur
    if (ret > 0 && event) {
      this->manage_event();
    }
  }

  //---------------------------
}
void Monitor::close() {
  //---------------------------

  udev_monitor_unref(usb_struct->monitor);
  udev_unref(usb_struct->udev);

  //---------------------------
}

//Subfunction
void Monitor::manage_event() {
  //---------------------------

  //Event associated device
  usb_struct->device = udev_monitor_receive_device(usb_struct->monitor);
  if (!usb_struct->device) return;

  std::string action = std::string(udev_device_get_action(usb_struct->device));
  std::string type = std::string(udev_device_get_devtype(usb_struct->device));
  std::string serial = std::string(udev_device_get_sysattr_value(usb_struct->device, "serial"));
  std::string vendor = std::string(udev_device_get_sysattr_value(usb_struct->device, "idVendor"));
  std::string product = std::string(udev_device_get_sysattr_value(usb_struct->device, "idProduct"));


  say("-----");
  say(action);
  say(type);
  say(serial);
  say(vendor);
  say(product);


  -> add / bind

  //realsense
-> usb_device
-> 103223061341
-> 8086
-> 0b5c
-> Intel(R) RealSense(TM) Depth Camera 455
-> Intel(R) RealSense(TM) Depth Camera 455

//kinect
-> usb_device
-> 000123924512
-> 045e
-> 097b
-> Generic
-> 4-Port USB 2.0 Hub



/*
  if (vendor && product) {
    std::string vendor_id = vendor;
    std::string product_id = product;

    // Replace with your Kinect's vendor ID and product ID
    if (vendor_id == "045E" && product_id == "02AE") {
      if (action == "remove") {
        std::cout << "Kinect device unplugged.\n";
        // Reset Kinect logic here
      }
    }
  }*/

  //Release device
  udev_device_unref(usb_struct->device);

  //---------------------------
}

}
