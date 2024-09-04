#pragma once

#include <libudev.h>


namespace usb::structure{

struct Udev{
  //---------------------------

  struct udev* contexte = nullptr;
  struct udev_monitor* monitor = nullptr;
  struct udev_device* device = nullptr;
  int fd;

  //---------------------------
};

}
