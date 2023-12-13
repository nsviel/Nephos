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

  this->t = timer.start_t();

  //---------------------------
}
void VK_profiler::stop(string name){
  //---------------------------

  float duration = timer.stop_ms(t);
  float time_beg = timer.get_time_start();
  float time_end = timer.get_time_stop();
  vk::structure::Task task = {time_beg, time_end, name};
  struct_vulkan->profiler.vec_task.push_back(task);

  //---------------------------
}
