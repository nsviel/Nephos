#pragma once

#include <Profiler/src/Profiler/Graph/Structure/Tasker.h>
#include <Utility/Specific/Common.h>
#include <Profiler/src/Timer/Chrono.h>

namespace prf::fps{class Counter;}
namespace prf::fps{class Control;}
namespace prf::graph::structure{class Task;}
namespace prf::graph::structure{class Tasker;}
namespace prf::improfil{class Manager;}


namespace prf::graph{

class Tasker : public prf::graph::structure::Tasker
{
public:
  //Constructor / Destructor
  Tasker(string name);
  ~Tasker();

public:
  //Main function
  void reset();

  //Loop function
  void loop_begin();
  void loop_begin(int fps);
  void loop_end();

  //Task function
  void task_begin(string name);
  void task_begin(string name, float time);
  void task_end(string name);
  void task_end(string name, float time);
  void task_end(string name, vec4 color);

  void task_follow_begin(string name);
  void task_follow_end(string name, float time);

  inline void set_vec_task(vector<prf::graph::structure::Task>& value){this->vec_task = value;}
  inline bool is_empty(){return this->vec_task.empty();}

private:
  prf::timer::Chrono timer;
  prf::fps::Counter* fps_counter;
  prf::fps::Control* fps_control;
};

}
