#include "VK_info.h"

#include <VK_struct/Namespace.h>


//Constructor / Destructor
VK_info::VK_info(vk::structure::Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_info::~VK_info(){}

//Main function
