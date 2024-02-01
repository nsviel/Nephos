#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/Chrono.h>


namespace utl::element{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler();
  ~Profiler();

public:
  //Main function
  void clear();

  //Task function
  void task_start();
  void task_stop(string name);

  std::chrono::time_point<std::chrono::system_clock> time_ref;

  inline vector<utl::type::Task>& get_vec_task(){return vec_task;}
  inline float get_fps(){return fps;}
  inline void set_fps(float value){this->fps = fps;}
  //inline void set_reference_time(float value){this->time_ref = fps;}

private:
  utl::timer::Chrono timer;

  vector<utl::type::Task> vec_task;
  utl::timer::Timepoint task_beg;
  float fps;
};

}
