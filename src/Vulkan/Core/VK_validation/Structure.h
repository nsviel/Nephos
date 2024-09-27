#pragma once

#include <Vulkan/Core/VK_shader/Structure/Info.h>
#include <Vulkan/Core/VK_shader/Structure/Module.h>


namespace vk::validation{

struct Structure{
  //---------------------------

  VkDebugUtilsMessengerCreateInfoEXT messenger_info;
  VkValidationFeaturesEXT feature_info;
  VkDebugUtilsMessengerEXT messenger;

  //---------------------------
};

}
