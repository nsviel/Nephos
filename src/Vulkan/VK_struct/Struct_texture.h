#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::structure{

struct Texture{
  //---------------------------

  utl::media::Image* utl_image;
  vk::structure::Image vk_image;
  vk::structure::Buffer stagger;

  std::string name = "hello";

  //---------------------------
};

}
