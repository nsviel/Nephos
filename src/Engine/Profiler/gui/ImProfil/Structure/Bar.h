#pragma once

#include <Profiler/src/Profiler/Graph/Structure/Task.h>
#include <vector>


namespace prf::improfil{

struct Bar{
  //---------------------------

  std::vector<prf::graph::structure::Task> vec_task;
  std::vector<std::size_t> task_stat_index;

  //---------------------------
};

}
