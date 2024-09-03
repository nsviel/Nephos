#include "Monitor.h"

#include <Utility/Namespace.h>


namespace sys{

//Constructor / Destructor
Monitor::Monitor(){
  //---------------------------

  //---------------------------
}
Monitor::~Monitor(){}

//Main function
void Monitor::usb_monitor() {
  //---------------------------

  struct udev* udev = udev_new();
  if (!udev) {
    std::cerr << "Can't create udev\n";
    return;
  }

  struct udev_monitor* mon = udev_monitor_new_from_netlink(udev, "udev");
  udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", "usb_device");
  udev_monitor_enable_receiving(mon);

  int fd = udev_monitor_get_fd(mon);

  while (true) {
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    int ret = select(fd + 1, &fds, NULL, NULL, NULL);
    if (ret > 0 && FD_ISSET(fd, &fds)) {
      struct udev_device* dev = udev_monitor_receive_device(mon);
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

  udev_monitor_unref(mon);
  udev_unref(udev);

  //---------------------------
}

}
