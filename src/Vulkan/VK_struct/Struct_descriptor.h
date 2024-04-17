#pragma once

#include <Utility/Specific/Common.h>


namespace vk::structure{

struct Descriptor{
  //---------------------------

  VkDescriptorSetLayout layout = VK_NULL_HANDLE;
  VkDescriptorSet set = VK_NULL_HANDLE;
  bool is_available = true;

  //---------------------------
};

}
