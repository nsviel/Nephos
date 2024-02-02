#include "Info.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Info::Info(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Info::~Info(){}

//Main function
string Info::get_gpu_name(){
  return struct_vulkan->device.physical_device.name;
}
vec4* Info::get_color_background(){
  return &struct_vulkan->param.background_color;
}


}
