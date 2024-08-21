#pragma once

#include <Profiler/src/Monitor/Profiler.h>
#include <list>


namespace prf::monitor{

struct Structure{
  //---------------------------

  std::list<prf::monitor::Profiler*> list_profiler;
  prf::monitor::Profiler profiler_main;
  bool pause = false;
  int max_time = 50;

  //---------------------------
};

}
