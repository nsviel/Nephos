#include "VK_extension.h"


//Constructor / Destructor
VK_extension::VK_extension(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_extension::~VK_extension(){}

//Main functions
void VK_extension::init(){
  //---------------------------

  struct_vulkan->instance.extension_khr.clear();
  struct_vulkan->instance.extension_khr.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
  struct_vulkan->instance.extension_khr.push_back(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME);

  //---------------------------
}
