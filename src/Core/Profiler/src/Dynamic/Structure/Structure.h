#pragma once

#include <Profiler/src/Dynamic/Profiler.h>
#include <list>


namespace prf::dynamic{

struct Structure{
  //---------------------------

  std::list<prf::dynamic::Profiler*> list_profiler;
  prf::dynamic::Profiler profiler_main;
  bool pause = false;
  int max_time = 50;

  //---------------------------
};

}
