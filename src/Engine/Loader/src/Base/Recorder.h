#pragma once

#include <Utility/Base/Type/Data.h>
#include <string>


namespace ldr::base{

struct Recorder{
  //---------------------------

  virtual void record_ascii(utl::base::Data* data){}
  virtual void record_binary(utl::base::Data* data){}

  std::string format = "";

  //---------------------------
};

}
