#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/UTL_specific/common.h>


class VK_validation
{
public:
  //Constructor / Destructor
  VK_validation(vk::structure::Vulkan* struct_vulkan);
  ~VK_validation();

public:
  //Main functions
  void create_validation_layer();
  void clean_layer();

  //Extension
  void* find_validation_extension();
  void* extension_debug(void* ptr);
  void* extension_feature(void* ptr);

  //Subfunction
  bool check_validation_layer_support();
  VkResult create_debug_EXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
  void destroy_debug_EXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

  inline vector<const char*> get_validation_layers(){return validation_layers;};

private:
  vk::structure::Vulkan* struct_vulkan;

  vector<const char*> validation_layers;
  bool with_validation_layer;
  bool with_best_practice;
  bool with_shader_printf;

  VkDebugUtilsMessengerCreateInfoEXT EXT_debug_info;
  VkDebugUtilsMessengerEXT EXT_debug;
  vector<VkValidationFeatureEnableEXT> EXT_enables;
  VkValidationFeaturesEXT EXT_feature;
};
