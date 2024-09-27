#pragma once

#include <Vulkan/Core/VK_shader/Structure/Info.h>
#include <Vulkan/Core/VK_shader/Structure/Module.h>


namespace vk::validation{

struct Structure{
  //---------------------------

  VkDebugUtilsMessengerEXT messenger;
  VkValidationFeaturesEXT feature;

  //---------------------------
};

}
