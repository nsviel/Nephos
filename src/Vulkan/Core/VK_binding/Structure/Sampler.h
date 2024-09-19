#pragma once

#include <Utility/Base/Media/Image.h>
#include <vulkan/vulkan.h>
#include <memory>
#include <string>


namespace vk::descriptor::structure{

struct Sampler{
  //---------------------------

  VkDescriptorType type = VK_DESCRIPTOR_TYPE_SAMPLER;
  std::shared_ptr<utl::media::Image> image = std::make_shared<utl::media::Image>();
  std::string name = "";
  int binding = 0;

  //---------------------------
};

}
