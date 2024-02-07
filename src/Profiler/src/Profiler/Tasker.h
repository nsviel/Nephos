#pragma once

#include <Utility/Specific/common.h>
#include <Profiler/src/Timer/Chrono.h>

namespace prf::fps{class Control;}
namespace prf::type{class Task;}


namespace prf{

class Tasker
{
public:
  //Constructor / Destructor
  Tasker();
  ~Tasker();

public:
  //Main function
  void clear();

  //Loop function
  void loop_begin();
  void loop_begin(int fps);
  void loop_end();

  //Task function
  void task_begin(string name);
  void task_end(string name);
  void task_end(string name, vec4 color);

  inline vector<prf::type::Task>& get_vec_task(){return vec_task;}
  inline float get_fps(){return fps;}
  inline void set_fps(float value){this->fps = value;}

private:
  prf::timer::Chrono timer;
  prf::fps::Control* fps_control;

  vector<prf::type::Task> vec_task_current;
  vector<prf::type::Task> vec_task;
  prf::timer::Timepoint reference;
  bool is_fps_control;
  float fps;
};

}
