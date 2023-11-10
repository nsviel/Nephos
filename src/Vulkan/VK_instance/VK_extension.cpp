#include "VK_extension.h"

#include <VK_main/Struct_vulkan.h>


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

  struct_vulkan->instance.extension_ext.clear();
  struct_vulkan->instance.extension_ext.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  struct_vulkan->instance.extension_ext.push_back(VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME);
  struct_vulkan->instance.extension_ext.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

  struct_vulkan->instance.extension_khr.clear();
  struct_vulkan->instance.extension_khr.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
  struct_vulkan->instance.extension_khr.push_back(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME);

  //---------------------------
}
