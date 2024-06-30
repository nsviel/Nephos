#pragma once

#include <Profiler/src/Hardware/Structure/Queue.h>
#include <vector>
#include <string>


namespace prf::hardware::structure{

struct GPU{
  //---------------------------

  std::string name;

  std::vector<prf::hardware::structure::Queue> vec_queue;
  float total_consumption = -1;
  float power_usage = -1;
  int temperature = -1;
  int temperature_max = -1;
  int fan_speed = -1;

  //---------------------------
};

}
