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

  double start_time;
  double end_time;
  std::string name;
  vec4 color;

  double GetLength(){
    return end_time - start_time;
  }

  //---------------------------
};

struct Frame_data{
  //---------------------------

  std::vector<utl::gui::serie::Graph_task> tasks;
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
