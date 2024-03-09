#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Physical_device{
  //---------------------------

  //Information
  std::string name;
  bool has_extension_support;
  bool discrete_gpu = false;
  uint32_t max_image_dim;
  uint64_t timestamp_period;
  int selection_score;
  int vendorID;

  //Properties
  VkPhysicalDevice handle;
  VkPhysicalDeviceProperties properties;
  VkPhysicalDeviceFeatures features;
  VkPhysicalDeviceType type;
  VkSurfaceCapabilitiesKHR capabilities;
  VkSampleCountFlagBits max_sample_count;

  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentation_mode;
  std::vector<vk::structure::queue::Family> vec_queue_family;

  //---------------------------
};

}
