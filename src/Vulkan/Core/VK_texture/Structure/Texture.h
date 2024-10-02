#pragma once

#include <Vulkan/Core/VK_image/Structure/Image.h>
#include <Vulkan/Core/VK_data/Structure/Buffer.h>
#include <Utility/Base/Data/Texture.h>
#include <string>


namespace vk::structure{

struct Texture{
  //---------------------------

  int UID = 0;

  //Actual texture components
  std::shared_ptr<utl::base::Image> image;
  vk::structure::Image wrapper;
  vk::data::structure::Buffer stagger;

  //For gui display
  VkDescriptorSet descriptor_set = VK_NULL_HANDLE;

  //---------------------------
};

}
