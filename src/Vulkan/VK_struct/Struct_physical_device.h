#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Queue_family{
  //---------------------------

  VkQueueFamilyProperties property;
  int nb_queue = 0;
  bool graphics = 0;
  bool compute = 0;
  bool transfer = 0;
  bool sparseBinding = 0;
  bool presentation = 0;

  //---------------------------
};

struct Physical_device{
  //---------------------------

  VkPhysicalDevice handle;
  VkPhysicalDeviceProperties properties;
  VkSurfaceCapabilitiesKHR capabilities;
  VkPhysicalDeviceFeatures features;
  VkPhysicalDeviceType type;
  VkSampleCountFlagBits max_sample_count;

  vector<VkSurfaceFormatKHR> formats;
  vector<VkPresentModeKHR> presentation_mode;

  std::string name;
  bool has_extension_support;
  uint32_t max_image_dim;
  uint64_t timestamp_period;
  int queue_family_graphics_idx = -1;
  int queue_family_transfer_idx = -1;
  int queue_family_presentation_idx = -1;
  int selection_score;
  int vendorID;

  //Queue number
  std::vector<Queue_family> vec_queue_family;

  //---------------------------
};

}
