#include "Monitor.h"

#include <USB/Namespace.h>
#include <Utility/Namespace.h>


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

  //---------------------------
}
void Monitor::usb_monitor() {
  //---------------------------

  while (true) {
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(usb_struct->fd, &fds);

    int ret = select(usb_struct->fd + 1, &fds, NULL, NULL, NULL);
    if (ret > 0 && FD_ISSET(usb_struct->fd, &fds)) {
      struct udev_device* dev = udev_monitor_receive_device(usb_struct->monitor);
      if (dev) {
        const char* action = udev_device_get_action(dev);
        const char* vendor = udev_device_get_sysattr_value(dev, "idVendor");
        const char* product = udev_device_get_sysattr_value(dev, "idProduct");

        if (vendor && product) {
          std::string vendor_id = vendor;
          std::string product_id = product;

          // Replace with your Kinect's vendor ID and product ID
          if (vendor_id == "045E" && product_id == "02AE") {
            if (std::string(action) == "remove") {
              std::cout << "Kinect device unplugged.\n";
              // Reset Kinect logic here
            }
          }
        }
        udev_device_unref(dev);
      }
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

}
