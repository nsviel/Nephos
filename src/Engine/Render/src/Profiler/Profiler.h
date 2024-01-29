#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Render/src/Profiler/Struct_profiler.h>
#include <Utility/Function/Timer/Chrono.h>

namespace eng::render{class Node;}


namespace eng::render{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(eng::render::Node* node_render);
  ~Profiler();

public:
  //Main function
  void task_start();
  void task_stop(string name);

private:
  utl::timer::Chrono timer;

  std::chrono::time_point<std::chrono::system_clock> time_ref;
  vector<eng::profiler::Task> vec_task;
  timer_time time_beg;
};

}
