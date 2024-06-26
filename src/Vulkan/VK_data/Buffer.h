#pragma once

namespace vk::memory{class Allocator;}
namespace vk::memory{class Transfer;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}
namespace vk::structure{class Buffer;}


namespace vk::data{

class Buffer
{
public:
  //Constructor / Destructor
  Buffer(vk::structure::Vulkan* vk_struct);
  ~Buffer();

public:
  //Main function
  void create_buffers(vk::structure::Object* vk_object);
  void update_buffer(vk::structure::Object* vk_object);
  void clean_buffers(vk::structure::Object* vk_object);
  void clean_buffer(vk::structure::Buffer* buffer);

  //Subfunction
  int get_size_buffer(vk::structure::Object* vk_object);

private:
  vk::structure::Vulkan* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
  vk::memory::Transfer* vk_mem_transfer;
};

}
