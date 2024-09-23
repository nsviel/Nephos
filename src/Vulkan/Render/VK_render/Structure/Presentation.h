#pragma once

#include <vulkan/vulkan.h>


namespace vk::render::structure{

struct Presentation{
  //---------------------------

  VkDescriptorSet descriptor_set = VK_NULL_HANDLE;

  //---------------------------
};

}
