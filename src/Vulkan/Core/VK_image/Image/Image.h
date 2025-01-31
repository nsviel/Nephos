#pragma once

namespace vk{class Structure;}
namespace vk::memory{class Allocator;}
namespace vk::image{class Format;}
namespace vk::image{class Ressource;}
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
  void init();
  void clean();

private:
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
  vk::image::Format* vk_format;
  vk::image::Ressource* vk_image;
};

}
