#pragma once

#include <Utility/Specific/common.h>
#include <Profiler/src/Timer/Chrono.h>

namespace prf::fps{class Counter;}
namespace prf::fps{class Control;}
namespace prf::graph{class Task;}
namespace prf::improfil{class Manager;}


namespace prf::graph{

class Tasker
{
public:
  //Constructor / Destructor
  Tasker(string name);
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
  void task_begin(string name, float time);
  void task_end(string name);
  void task_end(string name, float time);
  void task_end(string name, vec4 color);

  inline void set_vec_task(vector<prf::graph::Task>& value){this->vec_task = value;}
  inline vector<prf::graph::Task>& get_vec_task(){return vec_task;}
  inline float get_loop_fps(){return loop_fps;}
  inline prf::improfil::Manager* get_gui_graph(){return gui_graph;}
  inline std::string get_name(){return name;}
  inline bool is_empty(){return vec_task.empty();}

private:
  prf::timer::Chrono timer;
  prf::fps::Counter* fps_counter;
  prf::fps::Control* fps_control;
  prf::improfil::Manager* gui_graph;
  prf::timer::Timepoint reference;

  vector<prf::graph::Task> vec_task_current;
  vector<prf::graph::Task> vec_task;
  string name;
  float loop_fps;
  bool is_fps_control;
};

}
