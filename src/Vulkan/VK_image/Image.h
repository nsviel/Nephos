#pragma once

#include <Utility/Specific/common.h>

namespace vk::memory{class Allocator;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}


namespace vk::image{

class Image
{
public:
  //Constructor / Destructor
  Image(vk::structure::Vulkan* struct_vulkan);
  ~Image();

public:
  //Main function
  void create_image(vk::structure::Image* image);
  void clean_image(vk::structure::Image* image);

  //Image vulkan creation
  void create_image_obj(vk::structure::Image* image);
  void create_image_view(vk::structure::Image* image);
  void create_image_sampler(vk::structure::Image* texture);

  //Subfunction
  void image_layout_transition(VkCommandBuffer command_buffer, vk::structure::Image* image, VkImageLayout old_layout, VkImageLayout new_layout);
  void compute_mipmap(vk::structure::Image* image);
  void generate_mipmap(vk::structure::Image* image);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::memory::Allocator* vk_mem_allocator;
};

}
