#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::structure{

struct Image{
  //---------------------------

  //General info
  std::string name;
  int channel_nb = 4;
  int channel_byte = 1;

  //Dimension
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t size = 0;
  uint32_t mip_level_max = 1;
  uint32_t mip_level = 1;

  //Image info
  VkImage image;
  VkImageView view;
  VkImageTiling tiling;
  VkImageUsageFlags usage;
  VkImageAspectFlags aspect;
  VkImageLayout layout;

  //Other info
  VkFormat format = VK_FORMAT_R8G8B8A8_SRGB;
  VkDeviceMemory mem;
  VkMemoryPropertyFlags properties;
  VkSampler sampler;

  //---------------------------
};

}
