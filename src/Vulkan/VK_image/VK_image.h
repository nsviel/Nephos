#pragma once

#include <Utility/Specific/common.h>

namespace vk::command{class VK_memory;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}


class VK_image
{
public:
  //Constructor / Destructor
  VK_image(vk::structure::Vulkan* struct_vulkan);
  ~VK_image();

public:
  //Main function
  void create_image(vk::structure::Image* image);
  void clean_image(vk::structure::Image* image);

  //Image vulkan creation
  void create_image_obj(vk::structure::Image* image);
  void create_image_view(vk::structure::Image* image);
  void create_image_sampler(vk::structure::Image* texture);

  //Subfunction
  void compute_mipmap(vk::structure::Image* image);
  void generate_mipmap(vk::structure::Image* image);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::VK_memory* vk_memory;
};
