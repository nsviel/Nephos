#pragma once

#include <Profiler/Monitor/src/Component/Profiler.h>
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
