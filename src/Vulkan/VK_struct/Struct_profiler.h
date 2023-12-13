#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Task{
  //---------------------------

  float time_beg;
  float time_end;
  string name;
  
  //---------------------------
};

struct Profiler{
  //---------------------------

  vector<vk::structure::Task> vec_task;
  float engine_init;
  float engine_fps;

  //---------------------------
};

}
