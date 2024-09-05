#pragma once

#include <USB/src/Structure/Udev.h>
#include <Data/Namespace.h>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>


namespace usb{

struct Structure{
  //---------------------------

  std::unordered_map<std::string, std::shared_ptr<dat::base::Sensor>> map_device;
  usb::structure::Udev udev;

  //---------------------------
};

}
