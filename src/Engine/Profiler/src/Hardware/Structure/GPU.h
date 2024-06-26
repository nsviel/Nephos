#pragma once

#include <Profiler/src/Hardware/Structure/Queue.h>
#include <vector>
#include <string>


namespace prf::hardware{

struct GPU{
  //---------------------------

  std::string name;

  std::vector<prf::hardware::Queue> vec_queue;
  float total_consumption = -1;
  int temperature = -1;
  int power_usage = -1;
  int fan_speed = -1;

  //---------------------------
};

}
