#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/Chrono.h>


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
  void loop_end();

  //Task function
  void task_begin(string name);
  void task_end(string name);
  void task_end(string name, vec4 color);

  inline vector<utl::type::Task>& get_vec_task(){return vec_task;}
  inline float get_fps(){return fps;}
  inline void set_fps(float value){this->fps = value;}

private:
  utl::timer::Chrono timer;

  vector<utl::type::Task> vec_task_current;
  vector<utl::type::Task> vec_task;
  utl::timer::Timepoint reference;
  float fps;
};

}
