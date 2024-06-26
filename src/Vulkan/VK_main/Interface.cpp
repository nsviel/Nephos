#include "Interface.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Interface::Interface(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Interface::~Interface(){}

//Main function
void Interface::fill_profiler_info(){
  prf::vulkan::Profiler* prf_vulkan = vk_struct->profiler->prf_vulkan;
  prf::vulkan::Collector* prf_collector = prf_vulkan->get_prf_collector();
  //---------------------------

  prf_collector->collect_info(vk_struct);

  //---------------------------
}
string Interface::get_gpu_name(){
  return vk_struct->device.physical_device.name;
}
vec4* Interface::get_color_background(){
  return &vk_struct->param.background_color;
}
bool Interface::is_gpu_discrete(){
  return vk_struct->device.physical_device.discrete_gpu;
}

}
