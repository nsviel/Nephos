#pragma once

#include <Vulkan/Core/VK_image/Structure/Image.h>
#include <Vulkan/Core/VK_data/Structure/Buffer.h>
#include <Utility/Base/Data/Texture.h>
#include <string>


namespace vk::structure{

struct Texture{
  //---------------------------

  //Texture data
  int UID = 0;
  VkDescriptorSet descriptor_set = VK_NULL_HANDLE;
  vk::structure::Image surface;
  vk::structure::Buffer stagger;

  //Embedded image
  std::shared_ptr<utl::base::Image> image;
  std::shared_ptr<utl::base::Depth> depth;
  std::shared_ptr<utl::base::Storage> storage;

  //---------------------------
};

}
