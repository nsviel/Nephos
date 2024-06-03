#pragma once

#include <Utility/Base/Type/Data.h>
#include <Utility/Base/Type/Pose.h>
#include <vector>
#include <string>


namespace ldr::io{

enum Mode{
  ASCII = 0,
  BINARY = 1,
};

}

namespace ldr::base{

struct Exporter{
  //---------------------------

  virtual void export_ascii(utl::base::Data* data, utl::base::Pose* pose, std::string path){}
  virtual void export_binary(utl::base::Data* data, utl::base::Pose* pose, std::string path){}

  std::string format = "";
  std::vector<int> vec_mode;

  //---------------------------
};

}
