#pragma once

#include <GUI/Utils/ImProfil/Namespace.h>
#include <Utility/Specific/common.h>


namespace utl::gui::serie{

struct Task{
  //---------------------------

  double time_beg;
  double time_end;
  std::string name;
  vec4 color;

  //---------------------------
};

struct Bar{
  //---------------------------

  std::vector<utl::gui::serie::Task> vec_task;
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
