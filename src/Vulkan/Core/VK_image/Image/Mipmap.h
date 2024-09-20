#pragma once

namespace vk::memory{class Allocator;}
namespace vk{class Structure;}
namespace vk::structure{class Image;}


namespace vk::image{

class Mipmap
{
public:
  //Constructor / Destructor
  Mipmap(vk::Structure* vk_struct);
  ~Mipmap();

public:
  //Main function
  void compute_mipmap(vk::structure::Image& image);
  void generate_mipmap(vk::structure::Image& image);

private:
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
};

}
