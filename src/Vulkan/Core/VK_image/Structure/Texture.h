#pragma once

#include <Vulkan/Core/VK_image/Structure/Image.h>
#include <Vulkan/Core/VK_data/Structure/Buffer.h>
#include <Utility/Base/Media/Image.h>
#include <string>


namespace vk::structure{

struct Texture{
  //---------------------------

  //General
  int UID = 0;
  std::string name = "";

  //Structure
  std::shared_ptr<utl::media::Image> utl_image;
  vk::structure::Image vk_image;
  vk::data::structure::Buffer stagger;

  //---------------------------
};

}