#pragma once

#include "Task.h"
#include <vector>


namespace utl::improfil{

struct Bar{
  //---------------------------

  std::vector<utl::improfil::Task> vec_task;
  std::vector<std::size_t> task_stat_index;

  //---------------------------
};

}
