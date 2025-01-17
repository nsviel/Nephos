#pragma once

#include <Vulkan/Core/VK_shader/Structure/Info.h>
#include <Vulkan/Core/VK_shader/Structure/Module.h>
#include <vector>


namespace vk::validation{

struct Structure{
  //---------------------------

  std::vector<const char*> vec_layer;
  std::vector<VkValidationFeatureEnableEXT> vec_feature_enable;
  std::vector<VkValidationFeatureDisableEXT> vec_feature_disable;
  VkDebugUtilsMessengerCreateInfoEXT messenger_info;
  VkValidationFeaturesEXT feature_info;
  VkDebugUtilsMessengerEXT messenger;
  bool enable = true;

  //---------------------------
};

}
