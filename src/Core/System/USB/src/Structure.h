#pragma once

#include <USB/src/Structure/Device.h>
#include <libudev.h>
#include <vector>


namespace usb{

struct Structure{
  //---------------------------

  std::vector<usb::structure::Device> vec_device;
  struct udev* udev = nullptr;
  struct udev_monitor* monitor = nullptr;
  struct udev_device* device = nullptr;
  int fd;

  //---------------------------
};

}
