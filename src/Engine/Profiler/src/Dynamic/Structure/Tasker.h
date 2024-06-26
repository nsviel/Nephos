#pragma once

#include <Profiler/src/Dynamic/Structure/Task.h>
#include <Utility/GUI/Plot/ImProfil/Plot.h>
#include <Utility/Element/Timer/Chrono.h>
#include <vector>
#include <string>


namespace prf::graph::structure{

struct Tasker{
  //---------------------------

  utl::improfil::Plot plot;
  utl::timer::Timepoint reference;

  std::vector<prf::graph::structure::Task> vec_task_current;
  std::vector<prf::graph::structure::Task> vec_task;
  std::string name = "";
  std::string thread_ID = "";
  float fps = 0;
  bool is_fps_control = false;

  //---------------------------
};

}
