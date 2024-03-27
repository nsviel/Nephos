#pragma once

#include <Utility/Specific/Common.h>


namespace vk::structure{

struct Descriptor{
  //---------------------------

  VkDescriptorSetLayout layout;
  VkDescriptorSet set;
  bool is_available = true;

  //---------------------------
};

}
