#pragma once

#include <Vulkan/Core/VK_image/Structure/Image.h>
#include <vulkan/vulkan.h>
#include <memory>
#include <string>


namespace vk::descriptor::structure{

struct Sampler{
  //---------------------------

  VkDescriptorType type = VK_DESCRIPTOR_TYPE_SAMPLER;
  std::shared_ptr<vk::structure::Image> image;
  std::string name = "";
  int binding = 0;

  //---------------------------
};

}
