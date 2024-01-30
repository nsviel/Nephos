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

  double startTime;
  double endTime;
  std::string name;
  uint32_t color;

  double GetLength(){
    return endTime - startTime;
  }

  //---------------------------
};

struct Frame_data{
  std::vector<utl::gui::serie::Graph_task> tasks;
  std::vector<size_t> taskStatsIndex;
};

struct Task_stats{
  double maxTime;
  size_t priorityOrder;
  size_t onScreenIndex;
};

}
