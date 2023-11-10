#include "VK_info.h"

#include <VK_main/VK_engine.h>


//Constructor / Destructor
VK_info::VK_info(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();

  //---------------------------
}
VK_info::~VK_info(){}

//Main function
