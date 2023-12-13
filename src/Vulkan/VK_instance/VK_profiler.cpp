#include "VK_profiler.h"


//Constructor / Destructor
VK_profiler::VK_profiler(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_profiler::~VK_profiler(){}

//Main function
void VK_profiler::start(){
  //---------------------------

  this->time_beg = timer.get_time();

  //---------------------------
}
void VK_profiler::stop(string name){
  //---------------------------

  timer_time time_end = timer.get_time();
  double A = timer.duration_s(struct_vulkan->profiler.time_ref, time_beg);
  double B = timer.duration_s(struct_vulkan->profiler.time_ref, time_end);
  vk::structure::Task task = {A, B, name};
  struct_vulkan->profiler.vec_task.push_back(task);

  //---------------------------
}
