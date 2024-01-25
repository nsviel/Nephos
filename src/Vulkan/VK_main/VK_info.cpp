#include "VK_info.h"

#include <Vulkan/Namespace.h>


//Constructor / Destructor
VK_info::VK_info(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_info::~VK_info(){}

//Main function
string VK_info::get_gpu_name(){
  return struct_vulkan->device.physical_device.name;
}
float VK_info::get_fps(){
  return struct_vulkan->profiler.engine_fps;
}
int* VK_info::get_fps_max(){
  return &struct_vulkan->param.max_fps;
}
vec4* VK_info::get_color_background(){
  return &struct_vulkan->param.background_color;
}
vector<vk::structure::Task>& VK_info::get_profiler_data(){
  return struct_vulkan->profiler.vec_task;
}
