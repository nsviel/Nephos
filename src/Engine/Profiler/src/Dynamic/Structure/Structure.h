#pragma once

#include <Profiler/src/Dynamic/Structure/Task.h>
#include <Utility/GUI/Plot/ImProfil/Plot.h>
#include <Utility/Element/Timer/Chrono.h>
#include <vector>
#include <string>


namespace prf::dynamic{

struct Structure{
  //---------------------------

  utl::improfil::Plot plot;
  utl::timer::Timepoint reference;

  std::vector<prf::dynamic::Task> vec_task_current;
  std::vector<prf::dynamic::Task> vec_task;
  std::string name = "";
  std::string thread_ID = "";
  float fps = 0;
  bool is_fps_control = false;

  //---------------------------
};

}
