#pragma once

#include <Vulkan/Core/VK_image/Structure/Image.h>
#include <vulkan/vulkan.h>
#include <memory>
#include <string>


namespace vk::descriptor::structure{

struct Sampler{
  //---------------------------

  std::string name = "";
  std::shared_ptr<vk::structure::Image> image;
  int binding = 0;

  //---------------------------
};

}
