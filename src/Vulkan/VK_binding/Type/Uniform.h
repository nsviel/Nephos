#pragma once

#include <string>

namespace vk::memory{class Allocator;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Descriptor_required;}
namespace vk::binding::structure{class Binding;}
namespace vk::binding::structure{class Uniform;}


namespace vk::binding{

class Uniform
{
public:
  //Constructor / Destructor
  Uniform(vk::structure::Vulkan* vk_struct);
  ~Uniform();

public:
  //Main function
  void create_uniform_buffers(vk::binding::structure::Binding* binding);
  vk::binding::structure::Uniform* create_uniform_buffer(std::string name, size_t size, int binding);
  void clean_uniform(vk::binding::structure::Binding* binding);

  //uniform update
  template <typename T> void update_uniform(std::string uniform_name, vk::binding::structure::Binding* binding, T value);

  //Subfunction
  vk::structure::Descriptor_required uniform_point_size();
  vk::structure::Descriptor_required uniform_mvp();
  vk::structure::Descriptor_required uniform_edl();

private:
  vk::structure::Vulkan* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
};

}