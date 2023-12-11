#include "VK_info.h"

#include <Vulkan/VK_struct/Namespace.h>


//Constructor / Destructor
VK_info::VK_info(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_info::~VK_info(){}

//Main function
