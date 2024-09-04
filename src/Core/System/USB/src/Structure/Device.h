#pragma once

#include <string>


namespace usb::structure{

struct Device{
  //---------------------------

  std::string name = "";
  std::string vendor = "";
  std::string product = "";

  //---------------------------
};

}
