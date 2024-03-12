#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::structure{

struct Image{
  //---------------------------

  //General info
  std::string name = "";
  int channel_nb = 4;
  int channel_byte = 1;

  //Dimension
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t size = 0;
  uint32_t mip_level_max = 1;
  uint32_t mip_level = 1;

  //Image info
  VkImage image = VK_NULL_HANDLE;
  VkImageView view = VK_NULL_HANDLE;
  VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
  VkImageUsageFlags usage = 0;
  VkImageAspectFlags aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  VkImageLayout layout = VK_IMAGE_LAYOUT_UNDEFINED;

  //Other info
  VkFormat format = VK_FORMAT_R8G8B8A8_SRGB;
  VkDeviceMemory mem = VK_NULL_HANDLE;
  VkMemoryPropertyFlags properties = 0;
  VkSampler sampler = VK_NULL_HANDLE;

  //---------------------------
};

}
