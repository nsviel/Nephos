#pragma once

#include <Utility/Specific/common.h>

namespace vk::memory{class Memory;}
namespace vk::memory{class Transfer;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}
namespace vk::structure{class Buffer;}


namespace vk::data{

class Buffer
{
public:
  //Constructor / Destructor
  Buffer(vk::structure::Vulkan* struct_vulkan);
  ~Buffer();

public:
  //Main functions
  void create_buffers(vk::structure::Object* vk_object);
  void update_buffer(vk::structure::Object* vk_object);
  void clean_buffers(vk::structure::Object* vk_object);
  void clean_buffer(vk::structure::Buffer* buffer);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::memory::Memory* vk_memory;
  vk::memory::Transfer* vk_transfert;
};

}
