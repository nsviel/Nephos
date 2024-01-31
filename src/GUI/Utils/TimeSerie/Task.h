#pragma once

#include <GUI/Utils/TimeSerie/Namespace.h>
#include <Utility/Specific/common.h>


namespace utl::gui::serie{

struct Task{
  //---------------------------

  float time_beg;
  float time_end;
  std::string name;

  //---------------------------
};

struct Graph_task{
  //---------------------------

  double time_beg;
  double time_end;
  std::string name;
  vec4 color;

  double GetLength(){
    return time_end - time_beg;
  }

  //---------------------------
};

struct Bar{
  //---------------------------

  std::vector<utl::gui::serie::Graph_task> vec_task;
  std::vector<size_t> task_stat_index;

  //---------------------------
};

struct Task_stats{
  //---------------------------

  double max_time;
  size_t priority_order;
  size_t on_screen_index;

  //---------------------------
};

}
