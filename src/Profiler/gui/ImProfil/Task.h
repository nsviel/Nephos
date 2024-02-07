#pragma once

#include <Profiler/Namespace.h>
#include <Utility/Specific/common.h>


namespace prf::improfil{

struct Bar{
  //---------------------------

  std::vector<prf::type::Task> vec_task;
  std::vector<size_t> task_stat_index;

  //---------------------------
};

struct Stat{
  //---------------------------

  double max_time;
  size_t priority_order;
  size_t on_screen_index;

  //---------------------------
};

}
