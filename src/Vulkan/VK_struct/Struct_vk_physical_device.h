#pragma once

#include <VK_struct/Struct_vk_physical_device.h>
#include <UTL_specific/common.h>


struct Struct_vk_physical_device{
  //---------------------------

  VkPhysicalDevice physical_device;
  VkPhysicalDeviceProperties properties;
  VkSurfaceCapabilitiesKHR capabilities;
  VkPhysicalDeviceFeatures features;
  VkPhysicalDeviceType type;

  vector<VkSurfaceFormatKHR> formats;
  vector<VkPresentModeKHR> presentation_mode;

  std::string name;
  bool has_extension_support;
  uint32_t max_image_dim;
  int queue_graphics_idx = -1;
  int queue_presentation_idx = -1;
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
