#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk{class Structure;}


namespace vk::texture{

class Format
{
public:
  //Constructor / Destructor
  Format(vk::Structure* vk_struct);
  ~Format();

public:
  //Main function
  VkFormat find_vk_format(std::string format);

private:
  vk::Structure* vk_struct;
};

}
