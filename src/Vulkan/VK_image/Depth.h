#pragma once

#include <Utility/Specific/common.h>

namespace vk::image{class Image;}
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
  vk::image::Image* vk_image;
};

}
