#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

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
  int queue_family_graphics_idx = -1;
  int queue_family_transfer_idx = -1;
  int queue_family_presentation_idx = -1;
  int selection_score;
  int vendorID;

  //Queue number
  uint32_t nb_queue_family = 0;
  uint32_t nb_queue_graphics = 0;
  uint32_t nb_queue_compute = 0;
  uint32_t nb_queue_transfer = 0;
  uint32_t nb_queue_sparseBinding = 0;
  uint32_t nb_queue_presentation = 0;

  //---------------------------
};

}
