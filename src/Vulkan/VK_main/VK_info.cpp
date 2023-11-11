#include "VK_info.h"

#include <VK_main/Struct_vulkan.h>


//Constructor / Destructor
VK_info::VK_info(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_info::~VK_info(){}

//Main function
