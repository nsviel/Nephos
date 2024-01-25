#pragma once

#include <Utility/Specific/common.h>


class VK_image;
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}

class VK_depth
{
public:
  //Constructor / Destructor
  VK_depth(vk::structure::Vulkan* struct_vulkan);
  ~VK_depth();

public:
  //Main functions
  void create_depth_image(vk::structure::Image* depth);

  //Subfunctions
  bool find_stencil_component(VkFormat format);
  VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat find_depth_format();

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_image* vk_image;
};
