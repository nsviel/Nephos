#pragma once

#include <libudev.h>


namespace usb{

struct Structure{
  //---------------------------

  struct udev* udev = nullptr;
  struct udev_monitor* monitor = nullptr;
  int fd;

  //---------------------------
};

}
