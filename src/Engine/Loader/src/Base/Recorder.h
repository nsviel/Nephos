#pragma once

#include <Utility/Base/Type/Data.h>
#include <string>


namespace ldr::base{

struct Recorder{
  //---------------------------

  virtual void export_ascii(utl::base::Data* data){}
  virtual void export_binary(utl::base::Data* data){}

  std::string format = "";

  //---------------------------
};

}
