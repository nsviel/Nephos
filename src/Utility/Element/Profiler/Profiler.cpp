#include "Profiler.h"

#include <Utility/Namespace.h>


namespace utl::element{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------



  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::clear(){
  //---------------------------

  this->vec_task.clear();

  //---------------------------
}
void Profiler::time_reference(){
  //---------------------------

  this->clear();
  this->reference = timer.get_time();

  //---------------------------
}

//Task function
void Profiler::task_start(){
  //---------------------------

  this->task_beg = timer.get_time();

  //---------------------------
}
void Profiler::task_stop(string name){
  //---------------------------

  utl::timer::Timepoint task_end = timer.get_time();
  double A = timer.duration_s(reference, task_beg);
  double B = timer.duration_s(reference, task_end);
  utl::type::Task task = {A, B, name};
  this->vec_task.push_back(task);

  //---------------------------
}

}
