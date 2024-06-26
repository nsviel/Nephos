#pragma once

#include <Vulkan/VK_queue/Structure/Family.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>


namespace vk::structure{

struct Physical_device{
  //---------------------------

  //Information
  std::string name = "";
  uint32_t max_image_dim = 0;
  uint64_t timestamp_period = 0;
  bool has_extension_support = false;
  bool discrete_gpu = false;
  int selection_score = 0;
  int vendor_ID = 0;

  //Properties
  VkPhysicalDevice handle = VK_NULL_HANDLE;
  VkPhysicalDeviceProperties properties = {};
  VkPhysicalDeviceFeatures features = {};
  VkPhysicalDeviceType type = VK_PHYSICAL_DEVICE_TYPE_OTHER;
  VkSurfaceCapabilitiesKHR capabilities = {};
  VkSampleCountFlagBits max_sample_count = VK_SAMPLE_COUNT_1_BIT;

  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentation_mode;
  std::vector<vk::queue::structure::Family> vec_queue_family;

  //---------------------------
};

}
