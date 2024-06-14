#pragma once

#include <Utility/Namespace.h>
#include <string>


namespace ldr::base{

struct Path{
  //---------------------------

  std::string base = utl::path::get_current_parent_path_abs();
  std::string folder = utl::path::get_current_parent_path_abs();
  std::string name = "";
  std::string format = "";

  //---------------------------
};

}
