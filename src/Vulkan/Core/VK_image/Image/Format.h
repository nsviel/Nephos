#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk{class Structure;}
namespace vk::structure{class Image;}


namespace vk::image{

class Format
{
public:
  //Constructor / Destructor
  Format(vk::Structure* vk_struct);
  ~Format();

public:
  //Main function
  VkFormat find_vk_format(std::string format);
  VkImageUsageFlags find_usage_from_format(vk::structure::Image& image);
  bool check_image_format(vk::structure::Image& image);

private:
  vk::Structure* vk_struct;
};

}
