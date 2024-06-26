#pragma once

#include <Profiler/src/Profiler/Graph/Structure/Task.h>
#include <Profiler/gui/ImProfil/Plot.h>
#include <Profiler/src/Timer/Chrono.h>
#include <vector>
#include <string>


namespace prf::graph::structure{

struct Tasker{
  //---------------------------

  prf::improfil::Plot plot;
  prf::timer::Timepoint reference;

  std::vector<prf::graph::structure::Task> vec_task_current;
  std::vector<prf::graph::structure::Task> vec_task;
  std::string name = "";
  std::string thread_ID = "";
  float fps = 0;
  bool is_fps_control = false;

  //---------------------------
};

}
