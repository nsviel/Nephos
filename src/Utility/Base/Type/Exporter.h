#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Base/Media/File.h>


namespace utl::type{

struct Exporter{
  //---------------------------

  virtual void export_ascii(utl::type::Data* data){}
  virtual void export_binary(utl::type::Data* data){}

  std::string format = "";

  //---------------------------
};

}
