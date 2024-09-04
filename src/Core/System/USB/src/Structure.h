#pragma once

#include <USB/src/Structure/Reference.h>
#include <USB/src/Structure/Udev.h>
#include <unordered_map>
#include <vector>
#include <string>


namespace usb{

struct Structure{
  //---------------------------

  std::unordered_map<std::string, std::string> map_device;
  std::vector<usb::structure::Reference> vec_reference;
  usb::structure::Udev udev;

  //---------------------------
};

}
