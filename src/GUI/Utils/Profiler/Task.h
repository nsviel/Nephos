#pragma once

#include <GUI/Utils/Profiler/Namespace.h>
#include <Utility/Specific/common.h>


namespace profiler::gui{

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
  std::vector<profiler::gui::Graph_task> tasks;
  std::vector<size_t> taskStatsIndex;
};

struct Task_stats{
  double maxTime;
  size_t priorityOrder;
  size_t onScreenIndex;
};

}
