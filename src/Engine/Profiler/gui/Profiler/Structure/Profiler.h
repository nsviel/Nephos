#pragma once

#include <Utility/Specific/Common.h>


namespace prf::gui{

struct Profiler{
  //---------------------------

  virtual void show_profiler(){}
  virtual void show_info(){}
  virtual void show_command(){}

  //---------------------------
};

}
