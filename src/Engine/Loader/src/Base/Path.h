#pragma once

#include <Utility/Namespace.h>
#include <string>


namespace ldr::base{

struct Path{
  //---------------------------

  std::string base = "";
  std::string folder = "";
  std::string name = "";
  std::string format = "";

  //---------------------------
};

}
