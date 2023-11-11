#include "VK_render.h"

#include <VK_main/Struct_vulkan.h>


//Constructor / Destructor
VK_render::VK_render(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_render::~VK_render(){}

//Main function
