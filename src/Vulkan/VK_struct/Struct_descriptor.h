#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Descriptor{
  //---------------------------

  VkDescriptorSetLayout layout;
  VkDescriptorSet set;
  bool is_available = true;

  //---------------------------
};

}
