#pragma once

#include <Vulkan/Core/VK_image/Structure/Image.h>
#include <Vulkan/Core/VK_data/Structure/Buffer.h>
#include <Utility/Base/Media/Image.h>
#include <string>


namespace vk::structure{

struct Texture{
  //---------------------------

  std::shared_ptr<utl::media::Image> image;
  vk::structure::Image wrapper;
  vk::data::structure::Buffer stagger;

  //---------------------------
};

}
