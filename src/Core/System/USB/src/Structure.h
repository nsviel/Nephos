#pragma once

#include <USB/src/Structure/Device.h>
#include <USB/src/Structure/Udev.h>
#include <vector>


namespace usb{

struct Structure{
  //---------------------------

  std::vector<usb::structure::Device> vec_device;
  usb::structure::Udev udev;

  //---------------------------
};

}
