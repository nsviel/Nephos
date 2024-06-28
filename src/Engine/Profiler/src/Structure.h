#pragma once

#include <Profiler/src/Hardware/Structure/Structure.h>
#include <Profiler/src/Dynamic/Structure/Structure.h>


namespace prf{

struct Structure{
  //---------------------------

  prf::hardware::Structure hardware;
  prf::dynamic::Structure dynamic;

  //---------------------------
};

}
