#pragma once

#include <Utility/Specific/common.h>

namespace vk::image{class VK_image;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}


namespace vk::image{

class Depth
{
public:
  //Constructor / Destructor
  Depth(vk::structure::Vulkan* struct_vulkan);
  ~Depth();

public:
  //Main functions
  void create_depth_image(vk::structure::Image* depth);

  //Subfunctions
  bool find_stencil_component(VkFormat format);
  VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat find_depth_format();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::image::VK_image* vk_image;
};

}
