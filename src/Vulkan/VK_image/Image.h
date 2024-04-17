#pragma once

#include <Utility/Specific/Common.h>

namespace vk::memory{class Allocator;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}


namespace vk::image{

class Image
{
public:
  //Constructor / Destructor
  Image(vk::structure::Vulkan* vk_struct);
  ~Image();

public:
  //Main function
  void create_image(vk::structure::Image* image);
  void clean_image(vk::structure::Image* image);
  void clean_image_view(vk::structure::Image* image);

  //Image vulkan creation
  void create_image_handle(vk::structure::Image* image);
  void create_image_view(vk::structure::Image* image);
  void create_image_sampler(vk::structure::Image* texture);

  //Subfunction
  void compute_mipmap(vk::structure::Image* image);
  void generate_mipmap(vk::structure::Image* image);

private:
  vk::structure::Vulkan* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
};

}
