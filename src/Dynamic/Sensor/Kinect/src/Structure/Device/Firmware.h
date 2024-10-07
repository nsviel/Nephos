#pragma once

#include <k4a/k4a.hpp>
#include <string>


namespace k4n::str::device{

struct Firmware{
  //---------------------------

  k4a_hardware_version_t version = {0};
  std::string constructor = "";
  std::string color = "";
  std::string depth = "";
  std::string audio = "";
  std::string build = "";

  //---------------------------
};

}
