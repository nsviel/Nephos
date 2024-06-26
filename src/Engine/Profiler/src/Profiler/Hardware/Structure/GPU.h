#pragma once

#include <Profiler/src/Profiler/Hardware/Structure/Queue.h>
#include <vector>
#include <string>


namespace prf::hardware{

struct GPU{
  //---------------------------

  std::string name;
  std::vector<prf::hardware::Queue> vec_queue;

  //---------------------------
};

}
