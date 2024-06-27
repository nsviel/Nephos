#pragma once

namespace vk::memory{class Allocator;}
namespace vk{class Structure;}
namespace vk::structure{class Image;}


namespace vk::image{

class Image
{
public:
  //Constructor / Destructor
  Image(vk::Structure* vk_struct);
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
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
};

}
