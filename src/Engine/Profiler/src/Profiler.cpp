#include "Profiler.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::render{

//Constructor / Destructor
Profiler::Profiler(eng::render::Node* node_render){
  //---------------------------



  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::task_start(){
  //---------------------------

  this->task_beg = timer.get_time();

  //---------------------------
}
void Profiler::task_stop(string name){
  //---------------------------

  utl::timer::Timepoint task_end = timer.get_time();
  double A = timer.duration_s(time_ref, task_beg);
  double B = timer.duration_s(time_ref, task_end);
  utl::type::Task task = {A, B, name};
  this->vec_task.push_back(task);

  //---------------------------
}

}
