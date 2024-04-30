#pragma once

#include <Utility/Base/Type/Data.h>
#include <string>


namespace ldr::base{

struct Exporter{
  //---------------------------

  virtual void export_ascii(utl::type::Data* data){}
  virtual void export_binary(utl::type::Data* data){}

  std::string format = "";

  //---------------------------
};

}
