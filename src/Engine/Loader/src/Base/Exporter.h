#pragma once

#include <Utility/Base/Type/Data.h>
#include <string>


namespace ldr::base{

struct Exporter{
  //---------------------------

  virtual void export_ascii(utl::base::Data* data, utl::base::Pose* pose, std::string path){}
  virtual void export_binary(utl::base::Data* data, utl::base::Pose* pose, std::string path){}

  std::string format = "";

  //---------------------------
};

}
