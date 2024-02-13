#pragma once

#include <vulkan/vulkan.h>
#include <vector>
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
  vk::structure::Buffer stagger;

  //---------------------------
};

}
