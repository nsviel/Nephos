#pragma once

#include <Profiler/src/Profiler/Graph/Structure/Tasker.h>
#include <string>

namespace prf::fps{class Counter;}
namespace prf::fps{class Control;}
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

  void task_follow_begin(std::string name);
  void task_follow_end(std::string name, float time);

private:
  prf::timer::Chrono timer;
  prf::fps::Counter* fps_counter;
  prf::fps::Control* fps_control;
};

}
