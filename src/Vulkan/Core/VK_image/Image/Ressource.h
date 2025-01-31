#pragma once

namespace vk{class Structure;}
namespace vk::memory{class Allocator;}
namespace vk::image{class Format;}
namespace vk::structure{class Image;}


namespace vk::image{

class Ressource
{
public:
  //Constructor / Destructor
  Ressource(vk::Structure* vk_struct);
  ~Ressource();

public:
  //Main function
  void create_image(vk::structure::Image& image);
  void clean_image(vk::structure::Image& image);
  void clean_image_view(vk::structure::Image& image);

  //Subfunction
  void create_image_handle(vk::structure::Image& image);
  void create_image_view(vk::structure::Image& image);
  void create_image_sampler(vk::structure::Image& image);

private:
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
  vk::image::Format* vk_format;
};

}
