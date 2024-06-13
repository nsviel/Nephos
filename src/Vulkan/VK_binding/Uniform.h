#pragma once

#include <Utility/Specific/Common.h>

namespace vk::memory{class Allocator;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Binding;}
namespace vk::structure{class Uniform;}


namespace vk::binding{
  
class Uniform
{
public:
  //Constructor / Destructor
  Uniform(vk::structure::Vulkan* vk_struct);
  ~Uniform();

public:
  //Main function
  void create_uniform_buffers(vk::structure::Binding* binding);
  vk::structure::Uniform* create_uniform_buffer(string name, size_t size, int binding);
  void clean_uniform(vk::structure::Binding* binding);

  //uniform update
  template <typename T> void update_uniform(string uniform_name, vk::structure::Binding* binding, T value);

private:
  vk::structure::Vulkan* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
};

}
