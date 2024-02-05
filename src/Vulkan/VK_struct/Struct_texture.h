#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::structure{

struct Texture : public vk::structure::Image{
  //---------------------------

  //General info
  std::string name;
  int channel_nb = 4;
  int channel_byte = 1;
  uint32_t mip_level_max = 1;
  uint32_t mip_level = 1;

  //Dimension
  utl::media::Image* utl_image;

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
