#include "VK_profiler.h"


//Constructor / Destructor
VK_profiler::VK_profiler(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_profiler::~VK_profiler(){}

//Main function
