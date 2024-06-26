#pragma once

#include <Vulkan/VK_image/Structure/Image.h>
#include <Vulkan/VK_data/Structure/Buffer.h>
#include <string>


namespace vk::structure{

struct Texture{
  //---------------------------

  //General
  int UID = 0;
  std::string name = "";

  //Structure
  utl::media::Image* utl_image;
  vk::structure::Image vk_image;
  vk::data::structure::Buffer stagger;

  //---------------------------
};

}
