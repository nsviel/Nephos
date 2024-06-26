#pragma once

#include <Profiler/src/Profiler/Base/Profiler.h>


namespace prf::gui{

struct Profiler{
  //---------------------------

  virtual void show_profiler(prf::base::Profiler* profiler){}
  virtual void show_info(){}
  virtual void show_command(){}

  //---------------------------
};

}
