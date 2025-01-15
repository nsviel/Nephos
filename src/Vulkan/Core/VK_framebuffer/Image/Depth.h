#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk::image{class Image;}
namespace vk{class Structure;}
namespace vk::structure{class Image;}


namespace vk::image{

class Depth
{
public:
  //Constructor / Destructor
  Depth(vk::Structure* vk_struct);
  ~Depth();

public:
  //Main function
  void create_window_image(vk::structure::Image* depth);
  void create_screenshot_image(vk::structure::Image* depth);
  
  //Subfunctions
  bool find_stencil_component(VkFormat format);
  VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat find_depth_format();

private:
  vk::Structure* vk_struct;
  vk::image::Image* vk_image;
};

}
