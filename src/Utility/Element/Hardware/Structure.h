#pragma once

#include <Utility/Specific/Common.h>


namespace utl::hardware{

struct Structure{
  //---------------------------

  std::vector<float> vec_time;
  std::vector<float> cpu_temps;
  std::vector<float> gpu_temps;

  //---------------------------
};

}
