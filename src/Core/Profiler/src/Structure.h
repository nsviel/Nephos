#pragma once

#include <Profiler/src/Hardware/Structure/Structure.h>
#include <Profiler/src/Monitor/Structure/Structure.h>


namespace prf{

struct Structure{
  //---------------------------

  prf::hardware::Structure hardware;
  prf::monitor::Structure dynamic;

  //---------------------------
};

}
