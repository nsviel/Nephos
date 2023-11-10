#ifndef STRUCT_PHYSICAL_DEVICE_H
#define STRUCT_PHYSICAL_DEVICE_H

#include <VK_struct/Struct_physical_device.h>
#include <ELE_specific/common.h>


struct Struct_physical_device{
  //---------------------------

  VkPhysicalDevice physical_device;
  VkPhysicalDeviceProperties properties;
  VkSurfaceCapabilitiesKHR capabilities;

  vector<VkSurfaceFormatKHR> formats;
  vector<VkPresentModeKHR> presentation_mode;

  std::string name;
  uint32_t nb_queue_family;
  int queue_graphics_idx;
  int queue_presentation_idx;
  int selection_score;

  //---------------------------
};


#endif
