#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Task{
  //---------------------------

  double time_beg;
  double time_end;
  std::string name;

  //---------------------------
};

struct Profiler{
  //---------------------------

  std::chrono::time_point<std::chrono::system_clock> time_ref;
  vector<vk::structure::Task> vec_task;
  float engine_init;
  float engine_fps;

  //---------------------------
};

}
