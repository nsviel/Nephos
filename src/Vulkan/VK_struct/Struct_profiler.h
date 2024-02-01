#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Profiler{
  //---------------------------

  std::chrono::time_point<std::chrono::system_clock> time_ref;

  //---------------------------
};

}
