#include "Profiler.h"

#include <Vulkan/Namespace.h>


namespace vk::instance{

//Constructor / Destructor
Profiler::Profiler(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::start(){
  //---------------------------

  this->time_beg = timer.get_time();

  //---------------------------
}
void Profiler::stop(string name){
  //---------------------------

  timer_time time_end = timer.get_time();
  double A = timer.duration_s(struct_vulkan->profiler.time_ref, time_beg);
  double B = timer.duration_s(struct_vulkan->profiler.time_ref, time_end);
  utl::type::Task task = {A, B, name};
  struct_vulkan->param.vec_task.push_back(task);

  //---------------------------
}

}
