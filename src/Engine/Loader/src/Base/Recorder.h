#pragma once

#include <Utility/Base/Type/Data.h>
#include <string>


namespace ldr::base{

struct Recorder{
  //---------------------------

  std::string format = "";
  float size = 0;
  float ts_beg = 0;
  float ts_rec = 0;

  //---------------------------
};

}
