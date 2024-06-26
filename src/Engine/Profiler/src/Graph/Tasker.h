#pragma once

#include <Profiler/src/Graph/Structure/Tasker.h>
#include <string>

namespace utl::timer::fps{class Counter;}
namespace utl::timer::fps{class Control;}
namespace prf::graph::structure{class Task;}
namespace prf::graph::structure{class Tasker;}


namespace prf::graph{

class Tasker : public prf::graph::structure::Tasker
{
public:
  //Constructor / Destructor
  Tasker(std::string name);
  ~Tasker();

public:
  //Main function
  void reset();

  //Loop function
  void loop_begin(int fps = -1);
  void loop_end();

  //Task function
  void task_begin(std::string name, float time = -1);
  void task_end(const std::string& name, float time = -1, vec4 color = {});

  //Subfunction
  prf::graph::structure::Task* retrieve_task(const std::string& name);

  void task_follow_begin(std::string name);
  void task_follow_end(std::string name, float time);

private:
  utl::timer::Chrono timer;
  utl::timer::fps::Counter* fps_counter;
  utl::timer::fps::Control* fps_control;
};

}
